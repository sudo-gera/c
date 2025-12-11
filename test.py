
file = open('test.ppm', 'w')

print('P6', file=file)

width = 200

height = 200

print(width, height, file=file)

print(255, file=file)

file.flush()

for i in range(height):
    for j in range(width):
        for a in [round(i / height * 255), round(j / height * 255), 0]:
            file.buffer.write(a.to_bytes(1, 'big'))

