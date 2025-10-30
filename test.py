import numpy as np

def save_as_bmp32(filename, img: np.ndarray):
    h, w, _ = img.shape
    filesize = 54 + w * h * 4  # header + 4 bytes per pixel

    # BMP Header (14 bytes) + DIB Header (40 bytes)
    header = bytearray(54)
    header[0:2] = b'BM'
    header[2:6] = filesize.to_bytes(4, 'little')
    header[10:14] = (54).to_bytes(4, 'little')   # pixel data offset
    header[14:18] = (40).to_bytes(4, 'little')   # DIB header size
    header[18:22] = w.to_bytes(4, 'little')
    header[22:26] = h.to_bytes(4, 'little')
    header[26:28] = (1).to_bytes(2, 'little')    # color planes
    header[28:30] = (32).to_bytes(2, 'little')   # bits per pixel

    with open(filename, 'wb') as f:
        f.write(header)
        for row in img[::-1]:  # bottom-to-top
            bgrx = np.zeros((w, 4), dtype=np.uint8)
            bgrx[:, 0:3] = row[:, ::-1]  # BGR
            bgrx[:, 3] = 255             # Alpha = 255 (opaque)
            f.write(bgrx.tobytes())
img = (np.random.rand(100, 150, 3) * 255).astype(np.uint8)
save_as_bmp32("test32.bmp", img)
