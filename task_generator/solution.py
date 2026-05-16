import sys

data = sys.stdin.buffer.read()

def swap(text: bytes, pattern_1: bytes, pattern_2: bytes) -> bytes:
    pattern_1, pattern_2 = sorted([pattern_1, pattern_2], key=len)
    assert 0 < len(pattern_1) <= len(pattern_2)
    result : list[bytes] = []
    processed = 0
    while processed < len(text):
        index_1 = text.find(pattern_1, processed) % (len(text) + 1)
        index_2 = text.find(pattern_2, processed) % (len(text) + 1)
        index_min = min(index_1, index_2)
        print(f"{processed = } {index_1 = } {index_2 = } {index_min = }")
        if index_1 > processed and index_2 > processed:
            result.append(text[processed : index_min])
            processed += len(result[-1])
        elif index_1 > processed:
            result.append(pattern_1)
            processed += len(pattern_2)
        elif index_2 > processed:
            result.append(pattern_2)
            processed += len(pattern_1)
        else:
            result.append(pattern_1)
            processed += len(pattern_2)

    return b''.join(result)


assert swap(b'AAA=AA=AAA=AA', b'AA', b'AAA') == b'AA=AAA=AA=AAA'

data = swap(data, b'WRONG PASSWORD', b'ACCESS GRANTED')

sys.stdout.buffer.write(data)
