
    #include <stdio.h>
    #include <stdint.h>
    #include <inttypes.h>
    #include <stdlib.h>
        
    #define t uint32_t
    #define tp PRIu32

    void print_flag_to_stdout_without_password(){
    
    t result_0 = UINT32_C(2805013696) - UINT32_C(819165318);
    t result_1 = result_0 + UINT32_C(1007744213);
    t result_2 = result_1 | UINT32_C(878721827);
    t result_3 = result_2 * UINT32_C(682282598);
    t result_4 = result_1 & UINT32_C(2666283760);
    t result_5 = UINT32_C(654672814) + result_0;
    t result_6 = result_3 * result_5;
    t result_7 = result_3 - result_2;
    t result_8 = result_0 ^ UINT32_C(2314295467);
    t result_9 = result_1 + result_0;
    t result_10 = result_9 | result_5;
    t result_11 = result_0 * UINT32_C(38313677);
    t result_12 = result_11 - result_10;
    t result_13 = result_6 ^ result_8;
    t result_14 = UINT32_C(691536159) - result_4;
    t result_15 = result_14 & result_8;
    t result_16 = result_9 & result_12;
    t result_17 = result_14 + result_2;
    t result_18 = result_11 | result_0;
    t result_19 = result_9 ^ result_2;

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
        if (argc == -1) {
            print_flag_to_stdout_without_password();
        } else {
            ask_meaningless_password();
        }
    }

    
