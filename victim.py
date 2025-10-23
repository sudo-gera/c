with open('source', 'rb') as file:
    data = file.read()

# data = data.replace(
#     bytes.fromhex(' '.join('6b 14 00 1f   0b 01 00 00'.split()[::-1])),
#     bytes.fromhex(' '.join('6b 14 02 9f   0b 01 00 00'.split()[::-1])),
# )

# data = data.replace(
#     bytes.fromhex(' '.join('54 ff fe e1   6b 14 00 1f'.split()[::-1])),
#     bytes.fromhex(' '.join('54 ff fe e1   6b 14 02 9f'.split()[::-1])),
# )

data = data.replace(
    bytes.fromhex('54 ff fe e1   6b 14 00 1f')[::-1],
    bytes.fromhex('54 ff fe e1   6b 14 02 9f')[::-1],
)

with open('cracked', 'wb') as file:
    file.write(data)

