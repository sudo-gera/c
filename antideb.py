with open('antideb', 'rb') as file:
    data = file.read()


data = data.replace(
    bytes.fromhex('e8 e2 fe ff ff    48 83 f8 ff    75 14'),
    bytes.fromhex('e8 e2 fe ff ff    48 83 f8 ff    74 14'),
)

with open('antideb_patched', 'wb') as file:
    file.write(data)

