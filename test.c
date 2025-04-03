#include <stdio.h>

int main() {
    puts("hello world");
    [[gnu::assume(1.0000000000000001 > 1)]];
}
