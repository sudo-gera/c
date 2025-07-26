import sys
with open(sys.argv[1], 'rb') as file:
    data = file.read()

data = data.replace(
    bytes.fromhex('97ffffd2')[::-1],
    bytes.fromhex('97ffff6e')[::-1],
)

with open(sys.argv[2], 'wb') as file:
    file.write(data)
