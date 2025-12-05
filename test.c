#include <stdio.h>

int main() {
    const char* data = "    123 ";
    char c = 0;
    sscanf(data, " %c", &c);
    printf("%i\n", (int)c);
    printf("%c\n", c);
}
