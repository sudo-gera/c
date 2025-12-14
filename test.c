#include <stdio.h>

typedef struct pixel {
    char blue, green, red, opacity;
} pixel;

void save_as_bmp(const char* path, int cols, int rows, const pixel* pixels) {
    FILE* fp = fopen(path, "wb");
    if (!fp) {
        perror(path);
        return;
    }
    size_t size = cols * rows * sizeof(pixel);
    int head[13] = {size, 0, 54, 40, cols, rows, 0x200001, 0, 0, 0, 0, 0, 0};
    fwrite("BM", 2, 1, fp);
    fwrite(head, sizeof(head), 1, fp);
    fwrite(pixels, size, 1, fp);
    fclose(fp);
}

int main() {
    int width = 120, height = 80;
    struct pixel img[height * width];
    for (int y = 0; y < height; y++) {     // bottom to top
        for (int x = 0; x < width; x++) {  // left to right
            img[y * width + x].blue = y * 255 / height;
            img[y * width + x].green = x * 255 / width;
            img[y * width + x].red = 255 - y * 255 / height;
            img[y * width + x].opacity = -1;
        }
    }

    save_as_bmp("out.bmp", width, height, img);
}
