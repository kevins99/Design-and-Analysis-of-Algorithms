// #include <stdio.h>
// #include <string.h>

// FILE *input;
// int lc = 0, ptp = 1, rc = 0, pooltab[10];
// char inst[6][20];

// int main() {
//     pooltab[0] = 0;
//     input = fopen("ic.txt", "r");
//     char line_buf[10];

//     while(fgets(line_buf, sizeof(line_buf), input)) {
//         int count = 0;
//         int pos = 0;
//         for(int i = 0; line_buf[i] != "\n"; i++) {
//             if (line_buf[i] == ')'){
//                 inst[count][pos] = '\0';
//                 count++;
//             }
//             else if(line_buf[i])
//         }
//     }
//     fclose();
// }

#include <stdio.h>
#include <string.h>

void ltorg_alloc();

typedef struct MOTTAB {
    char mnemonic[10];
    int code;
    char class[5];
    int operands;
};

FILE *input;
int lc = 0, ptp = 1, rc = 0, pooltab[10];
char inst[6][40];

int main() {
    pooltab[0] = 0;
    input = fopen("output.txt", "r");
    char line_buf[80];

    while(fgets(line_buf, sizeof line_buf, input) != NULL) {
        int count = 0, pos = 0;
        for(int i = 0; line_buf[i] != '\n'; i++) {
            if(line_buf[i] == ')') {
                inst[count][pos] = '\0';
                count++;
            }
            else if(line_buf[i] == '(') pos = 0;
            else if(line_buf[i] == ',') {
                inst[count][pos] = '\0';
                pos = 0;
                count++;
            }
            else {
                inst[count][pos] = line_buf[i];
                pos++;
            }
        }

        if(!strcmp(inst[0], "AD") && !strcmp(inst[1], "2")) { // End stmt

        }   
        else if(!strcmp(inst[0], "AD") && !strcmp(inst[1], "3")) { // Ltorg stmt
            ltorg_alloc();
        }
        else if(!strcmp(inst[0], "AD") && !strcmp(inst[1], "1")) { // Start stmt

        }
        else if(!strcmp(inst[0], "AD") && !strcmp(inst[1], "4")) { // Origin stmt

        }
        else if(!strcmp(inst[0], "DL")) { // Declarative stmt
            if(!strcmp(inst[1], "1")) { // DS

            }
            else if(!strcmp(inst[1], "2")) { // DC

            }
        }
        else if(!strcmp(inst[0], "IS")) { // Imperative stmt
        
        }
    }
    fclose(input);

    return 0;
}

void ltorg_alloc() {
    for(int i = pooltab[ptp]; i < lc ; i++) {

    }
}