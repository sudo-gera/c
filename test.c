#include <stdio.h>

struct pixel{
    char blue, green, red, opacity;
};

void save_as_bmp(const char* filepath, const struct pixel* data, int cols, int rows){
    FILE* fp = fopen(filepath, "wb");
    if (!fp){
        perror(filepath);
        return;
    }
    fwrite("BM", 2, 1, fp);
    int size = sizeof(struct pixel) * cols * rows;
    int header[13] = {
        size + 54,
        0, 54, 40,
        cols,
        rows,
        0x200001,
    };
    fwrite(header, sizeof(header), 1, fp);
    fwrite(data, size, 1, fp);
    fclose(fp);
}


