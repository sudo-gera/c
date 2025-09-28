#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void save_as_bmp32(const char *filename, const unsigned char *img, int width, int height) {
    int filesize = 54 + 4 * width * height;

    unsigned char header[54] = {0};
    // BMP signature
    header[0] = 'B'; header[1] = 'M';
    // File size
    *(int*)&header[2] = filesize;
    // Pixel data offset
    *(int*)&header[10] = 54;
    // DIB header size
    *(int*)&header[14] = 40;
    // Width & height
    *(int*)&header[18] = width;
    *(int*)&header[22] = height;
    // Planes
    *(short*)&header[26] = 1;
    // Bits per pixel
    *(short*)&header[28] = 32;

    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("fopen");
        return;
    }
    fwrite(header, 1, 54, f);

    // Write pixels bottom-to-top in BGRA
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            const unsigned char *px = img + (y * width + x) * 3;
            unsigned char bgra[4] = { px[2], px[1], px[0], 255 }; // B, G, R, A=255
            fwrite(bgra, 1, 4, f);
        }
    }

    fclose(f);
}
int main() {
    int w = 100, h = 100;
    unsigned char *img = malloc(w * h * 3);

    // Fill with gradient
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            img[(y*w + x)*3 + 0] = x % 256; // R
            img[(y*w + x)*3 + 1] = y % 256; // G
            img[(y*w + x)*3 + 2] = 128;     // B
        }
    }

    save_as_bmp32("test32.bmp", img, w, h);
    free(img);
    return 0;
}
