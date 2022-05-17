struct winsize
  {
    unsigned short int ws_row;
    unsigned short int ws_col;
    unsigned short int ws_xpixel;
    unsigned short int ws_ypixel;
  };


// struct termio
//   {
//     unsigned short int c_iflag;
//     unsigned short int c_oflag;
//     unsigned short int c_cflag;
//     unsigned short int c_lflag;
//     unsigned char c_line;
//     unsigned char c_cc[8];
// };



extern int ioctl (int __fd, unsigned long int __request, ...) __attribute__ ((__nothrow__ ));


int main (int argc, char **argv)
{
    struct winsize w;
    ioctl(1, 0x5413, &w);

    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);
    return 0;
}
