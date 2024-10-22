import random

Bytes = bytes | bytearray

<<<<<<< HEAD
class Sign:
=======
class Signer:
>>>>>>> 550e90b37f478fcee644803cf61b9cd43b7d7274
    def __init__(self, hash_len: int):
        assert isinstance(hash_len, int)
        assert hash_len >= 0
        self.hash_len = hash_len

    def static_hash(self, data: Bytes) -> Bytes:
        return random.Random(data).randbytes(self.hash_len)

    def check(self, data: Bytes) -> bytes:
        if isinstance(data, bytearray):
            data = bytes(data)
        assert isinstance(data, bytes)
        return data

    def sign(self, data: Bytes) -> Bytes:
        data = self.check(data)
        return self.static_hash(data) + data

    def unsign(self, data: Bytes) -> Bytes:
        data = self.check(data)
        h, data = data[:self.hash_len], data[self.hash_len:]
        if self.static_hash(data) != h:
            raise ValueError('Invalid checksum.')
        return data

if __name__ == '__main__':
    raw_data = b'it works!'
<<<<<<< HEAD
    signer = Sign(8)
=======
    signer = Signer(8)
>>>>>>> 550e90b37f478fcee644803cf61b9cd43b7d7274
    signed_data = signer.sign(raw_data)
    assert len(signed_data) == len(raw_data) + signer.hash_len
    assert signer.unsign(signed_data) == raw_data
    failed_data = bytearray(signed_data)
    failed_data[-1] ^= 1
    try:
        signer.unsign(failed_data)
        assert False
    except ValueError:
        pass

<<<<<<< HEAD
assert Sign(8).sign(b'it works!')
assert Sign(8).unsign(Sign(8).sign(b'it works!')) == b'it works!'
=======
assert Signer(8).sign(b'it works!')
assert Signer(8).unsign(Signer(8).sign(b'it works!')) == b'it works!'
>>>>>>> 550e90b37f478fcee644803cf61b9cd43b7d7274
