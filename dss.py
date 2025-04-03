import sys
data = sys.stdin.buffer.read()


data = data.replace(
    bytes.fromhex('d9 45 08   d9 45 08   d8 c1'),
    bytes.fromhex('d9 45 08   d9 eb 90   de c9'),
)

sys.stdout.buffer.write(data)




