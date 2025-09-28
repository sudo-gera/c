#include <stdio.h>
#include <stdint.h>

void save_bmp32(const char*fn,unsigned char*img,int w,int h){
    int fs=54+4*w*h,z=0,o=54,d=40;short p=1,bpp=32;
    FILE*f=fopen(fn,"wb");
    fwrite("BM",1,2,f);fwrite(&fs,4,1,f);fwrite(&z,4,1,f);
    fwrite(&o,4,1,f);fwrite(&d,4,1,f);fwrite(&w,4,1,f);fwrite(&h,4,1,f);
    fwrite(&p,2,1,f);fwrite(&bpp,2,1,f);fwrite(&z,4,1,f);
    for(int y=h-1;y>=0;y--)for(int x=0;x<w;x++){
        unsigned char*p=img+(y*w+x)*3,b[4]={p[2],p[1],p[0],255};
        fwrite(b,4,1,f);
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
