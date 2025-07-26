int calc(int exponent, int base) {
    int result = 1;
    int i;

    for (i = 0; i < exponent; i++) {
        result = result * base;
    }
    
    return result;
}
