#include <stdio.h>

struct pixel{
    char blue, green, red, opacity;
};

void save_as_bmp(const char* filepath, int width, int height, struct pixel* pixels){
    int sizeof_pixels = width * height * sizeof(struct pixel);
    int header[13] = {
        sizeof_pixels + 54,
        0, 54, 40,
        width, height,
        0x200001,
    };
    FILE* fp = fopen(filepath, "wb");
    fwrite( "BM",   2,              1, fp );
    fwrite( header, sizeof(header), 1, fp );
    fwrite( pixels, sizeof_pixels,  1, fp );
    fclose( fp );
}

int main() {
    int width = 120, height = 80;
    struct pixel img[height * width];
    for (int y = 0; y < height; y++) { // bottom to top
        for (int x = 0; x < width; x++) { // left to right
            img[y * width + x].blue  = y * 255 / height;
            img[y * width + x].green = x * 255 / width;
            img[y * width + x].red   = 255 - y * 255 / height;
            img[y * width + x].opacity = -1;
        }
    }

    save_as_bmp("out.bmp", width, height, img);
}
