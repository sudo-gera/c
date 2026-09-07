import urllib.request
import dataclasses
import typing
import json
import pathlib
import datetime
import requests

import cache

@dataclasses.dataclass
class _OneDownloader:
    current_cache: cache.ICache

    def download_bytes(self, url: str) -> bytes:
        if url in self.current_cache:
            return self.current_cache[url]
        headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
            "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8",
            "Accept-Language": "en-US,en;q=0.9",
            "Accept-Encoding": "gzip, deflate, br",
            "Connection": "keep-alive",
            "Upgrade-Insecure-Requests": "1",
            "Sec-Ch-Ua": '"Not_A Brand";v="8", "Chromium";v="120", "Google Chrome";v="120"',
            "Sec-Ch-Ua-Mobile": "?0",
            "Sec-Ch-Ua-Platform": '"Windows"'
        }
        response = requests.get(url, headers=headers)
        data = response.content
        self.current_cache[url] = data
        return data

    def download_str(self, url: str) -> str:
        return self.download_bytes(url).decode()

    def download_json(self, url: str) -> typing.Any:
        return json.loads(self.download_str(url))

@dataclasses.dataclass
class _Downloader:
    permanent: _OneDownloader
    temporary: _OneDownloader

class Downloader(_Downloader):
    
    def __init__(self, dir: pathlib.Path) -> None:
        perm_cache = cache.Cache(dir)
        temp_cache = cache.TTLCache(perm_cache, datetime.timedelta(seconds=3600))
        super().__init__(
            permanent=_OneDownloader(perm_cache),
            temporary=_OneDownloader(temp_cache),
        )

