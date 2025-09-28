#include <stdio.h>
#include <stdint.h>

void save_bmp32(const char *fn, const unsigned char *img, int w, int h) {
    int fs = 54 + 4*w*h;
    unsigned char hdr[54] = {
        'B','M', fs,fs>>8,fs>>16,fs>>24, 0,0,0,0, 54,0,0,0,
        40,0,0,0, w,w>>8,w>>16,w>>24, h,h>>8,h>>16,h>>24,
        1,0, 32,0
    };
    FILE *f = fopen(fn,"wb");
    fwrite(hdr,1,54,f);
    for (int y=h-1;y>=0;y--)
        for (int x=0;x<w;x++) {
            const unsigned char *p = img + (y*w+x)*3;
            unsigned char bgra[4]={p[2],p[1],p[0],255};
            fwrite(bgra,1,4,f);
        }
    fclose(f);
}
int main() {
    int w=64,h=64;
    unsigned char img[w*h*3];
    for(int y=0;y<h;y++)for(int x=0;x<w;x++){
        img[(y*w+x)*3+0]=x*4;     // R
        img[(y*w+x)*3+1]=y*4;     // G
        img[(y*w+x)*3+2]=128;     // B
    }
    save_bmp32("out.bmp",img,w,h);
}
