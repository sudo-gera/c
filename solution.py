import sys
with open(sys.argv[1], 'rb') as file:
    data = file.read()

data = data.replace(
    bytes.fromhex('75 0c'),
    bytes.fromhex('90 90'),
)

with open(sys.argv[2], 'wb') as file:
    file.write(data)
