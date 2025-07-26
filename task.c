
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
      
#define t uint32_t
#define tp PRIu32

void print_flag_to_stdout_without_password(){

    t result_0 = UINT32_C(3045143558) | UINT32_C(3481897110);
    t result_1 = UINT32_C(2065998056) + result_0;
    t result_2 = result_1 * result_1;
    t result_3 = result_0 * UINT32_C(2616386405);
    t result_4 = result_0 * result_2;
    t result_5 = result_3 ^ result_2;
    t result_6 = result_3 ^ result_3;
    t result_7 = UINT32_C(2200752689) ^ result_4;
    t result_8 = result_3 - result_4;
    t result_9 = result_3 * result_0;
    t result_10 = result_8 - result_9;
    t result_11 = result_1 & result_7;
    t result_12 = result_6 & result_0;
    t result_13 = result_8 | result_1;
    t result_14 = result_9 + UINT32_C(822207024);
    t result_15 = result_6 - result_8;
    t result_16 = result_5 ^ result_1;
    t result_17 = result_5 & result_4;
    t result_18 = result_4 - result_14;
    t result_19 = result_13 - UINT32_C(258585180);

    t flag = result_19;
    printf("FLAG_%" tp "\n", flag);
}

void ask_meaningless_password(){
    char password[1024]; // Buffer of size 50

    printf("Enter password:");
    scanf("%49s", password); 

    printf("No flag for this password, sorry.\n");
}

int main(int argc, char**argv){
    if (argc != -1) {
        print_flag_to_stdout_without_password();
    } else {
        ask_meaningless_password();
    }
}


