#include <stdio.h>

void save_bmp32(const char *fn, void *img, int w, int h){
    int r[52]={54+4*w*h,0,54,40,w,h,0x200001};
    FILE*f=fopen(fn,"wb");
    fwrite("BM",1,2,f);
    fwrite(r,52,1,f);
    fwrite(img, w*h*4, 1, f);
    fclose(f);
}

int main() {
    int w = 64, h = 64;
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
