import hashlib
import dataclasses
import pathlib
import functools
import datetime
import abc
import uuid
import json
import typing
import logging

import utils_for_typing

@utils_for_typing.cache
def keyhash(key: str) -> str:
    return hashlib.sha256(key.encode()).hexdigest()

class ICache(abc.ABC):

    @abc.abstractmethod
    def key_to_path(self, key: str) -> pathlib.Path:
        ...

    def __getitem__(self, key: str) -> bytes:
        path = self.key_to_path(key)
        with path.open('rb') as file:
            return file.read()
    
    def __setitem__(self, key: str, data: bytes) -> None:
        path = self.key_to_path(key)
        with path.open('wb') as file:
            file.write(data)

    def __delitem__(self, key: str) -> None:
        path = self.key_to_path(key)
        path.unlink()

    def __contains__(self, key: str) -> bool:
        path = self.key_to_path(key)
        return path.exists()

@dataclasses.dataclass
class Cache(ICache):
    dir: pathlib.Path

    def __post_init__(self) -> None:
        self.dir.mkdir(parents=True, exist_ok=True)
    
    def key_to_path(self, key: str) -> pathlib.Path:
        return self.dir / keyhash(key)

@dataclasses.dataclass
class _TTL_name:
    cache: Cache
    key: str
    delay: datetime.timedelta

    def __post_init__(self) -> None:
        if self.delay <= datetime.timedelta():
            raise ValueError(f"Delay should be positive.")

    def get_block_begin(self, point: datetime.datetime) -> datetime.datetime:
        epoch = datetime.datetime(
            1970, 1, 1,
            tzinfo=datetime.timezone.utc,
        )
        from_epoch_to_point = point - epoch
        return point - from_epoch_to_point % self.delay

    def key_for_block(self, block_begin: datetime.datetime) -> str:
        return f"{block_begin}={block_begin + self.delay}={self.key}"

    def time_based_key(self) -> str:
        now = datetime.datetime.now(datetime.timezone.utc)

        block_begin = self.get_block_begin(now)

        for point in [block_begin, block_begin - self.delay]:
            block_key = self.key_for_block(point)
            if block_key in self.cache:
                data = json.loads(self.cache[block_key].decode())
                created_at_str = typing.cast(str, data["created_at"])
                created_at = datetime.datetime.fromisoformat(created_at_str)
                if now - self.delay < created_at:
                    return typing.cast(str, data['key'])

        payload = json.dumps(
            {
                "created_at": now.isoformat(),
                "key": uuid.uuid4().hex,
            }
        ).encode()

        self.cache[self.key_for_block(block_begin)] = payload

        return self.time_based_key()

@dataclasses.dataclass
class TTLCache(ICache):
    cache: Cache
    delay: datetime.timedelta

    def key_to_path(self, key: str) -> pathlib.Path:
        return self.cache.key_to_path(
            _TTL_name(
                self.cache,
                key,
                self.delay,
            ).time_based_key()
        )
