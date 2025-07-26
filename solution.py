import sys
with open(sys.argv[1], 'rb') as file:
    data = file.read()

data = data.replace(
    bytes.fromhex('75 0c'),
    bytes.fromhex('90 90'),
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
    bytes.fromhex('75 0c'),
    bytes.fromhex('90 90'),
=======
    bytes.fromhex('97ffffd2')[::-1],
    bytes.fromhex('97ffff6e')[::-1],
>>>>>>> a87d2fb9fe3890a1bddb07794c135ddad0685374
>>>>>>> 230ab61b7037a0787a12e7044c83c2ad95502196
>>>>>>> c6eb863bf79cfed6f685dc3d2583b88cd06a1fb5
)

with open(sys.argv[2], 'wb') as file:
    file.write(data)
