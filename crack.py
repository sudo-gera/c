with open('source', 'rb') as file:
    data = file.read()


data = data.replace(
    bytes.fromhex('3d 94 88 01 00 75 11'),
    bytes.fromhex('3d 94 88 01 00 90 90'),
)

with open('cracked', 'wb') as file:
    file.write(data)

