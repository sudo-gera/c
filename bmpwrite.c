#include <stdio.h>

void save_bmp32(const char* filepath, void* img, int width, int height){
    int header[13]={
        54 + 4 * width * height,
        0, 54, 40,
        width, height,
        0x200001
    };
    FILE* f = fopen(filepath,"wb");
    fwrite( "BM",   2,                    1,   f );
    fwrite( header, sizeof(header),       1,   f );
    fwrite( img,    width * height * 4,   1,   f );
    fclose( f );
}

int main() {
    int w = 120, h = 100;
    unsigned char img[w * h * 4];

    for (int y = 0; y < h; y++) { // bottom to top
        for (int x = 0; x < w; x++) { // left to right
            img[(y*w+x)*4+0] = x*4; // B
            img[(y*w+x)*4+1] = 0;   // G
            img[(y*w+x)*4+2] = y*4; // R
            img[(y*w+x)*4+3] = 255; // A
        }
    }

    save_bmp32("out.bmp", img, w, h);
}
