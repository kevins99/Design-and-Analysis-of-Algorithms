#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int sym_search(char sym[10]);
int mnemonic_search(char mnemonic[10]);
void sym_update(int stp, char value[10]);
void ltorg_allocation();
int evaluate(char exp[10]);
int is_register(char exp[10]);

typedef struct  MOTTAB {
        char mnemonic[10];
        int code;
        char class[5];
        int operands;
} MOTTAB;

MOTTAB mottab[18] = {
    {"ADD",1,"IS",2},
    {"BC",7,"IS",1},
    {"COMP",6,"IS",2},
    {"DIV",8,"IS",2},
    {"END",2,"AD",0},
    {"EQU",5,"AD",2},
    {"DC",1,"DL",1},
    {"DS",2,"DL",1},
    {"MOVER",4,"IS",2},
    {"MOVEM",5,"IS",2},
    {"LTORG",3,"AD",0},
    {"MULT",3,"IS",2},
    {"ORIGIN",4,"AD",0},
    {"PRINT",10,"IS",1},
    {"READ",9,"IS",1,},
    {"STOP",0,"IS",0},
    {"SUB",2,"IS",2},
    {"START",1,"AD",0},
};

typedef union lov {
    int length;
    char value[5];
}lov;

typedef struct SYMTAB {
    int sr_no;
    char symbol[10];
    int add;
    lov var;
} SYMTAB;

typedef struct LITTAB {
    int sr_no;
    char name[10];
    int add;
} LITTAB;

//Initialization
FILE *input;
SYMTAB symbol[20];
LITTAB littab[20];

int lc = 0, ptp = 0, rc = 0, stp = 0, ltp = 0;
int pooltab[20] = {0};
char inst[4][20];

int main() {
    input = fopen("input.txt", "r");
    char line_buf[20];
    pooltab[0] = 1;

    while(fgets(line_buf,sizeof line_buf,input) != NULL) {
        int count = 0, flag = 0;
        for(int i = 0; line_buf[i] != '\n';) {
            int pos = 0;
            while(line_buf[i] != '\t' && line_buf[i] != '\n') {
                inst[count][pos] = line_buf[i];
                pos++;
                i++;
            }
            if(pos) {
                count++;
                inst[count-1][pos] = '\0';
            }
            else i++;
        }
        
        if(inst[0] == "LTORG") ltorg_allocation();     // Ltorg address allocation
        else if (inst[0] == "START") {
            lc = atoi(inst[1]);
            printf("(AD, 1) (C, %d)\n", lc);
        }
        else if (inst[0] == "ORIGIN") {
            lc = evaluate(inst[1]);
            printf("(AD, 4) (C, %d)\n", lc);
        }
        else if(mnemonic_search(inst[1]) != -1) {      //Label exists
            int label_pos = sym_search(inst[0]), mnem_pos = mnemonic_search(inst[1]);
            
            if(label_pos != -1) {
                sym_update(label_pos, inst[0]);
            }
            else {
                sym_update(stp, inst[0]);
                stp++;
            }

            if(inst[1] == "DC") {
                printf("(DL, 1) (C, %s)\n", inst[2]);
                lc++;
            }
            else if(inst[1] == "DS") {
                printf("(DL, 2) (c, %s)\n", inst[2]);
                lc += atoi(inst[2]);
            }
            else {
                int code = mottab[mnemonic_search(inst[1])].code, rc = is_register(inst[2]);
                printf("(IS, %d)", code);

                if(rc == -1) printf(" (L, %d)", lit_update(inst[2]));
                else printf(" ");
            }
        }
        else if(mnemonic_search(inst[0]) != -1) {       // No label
            int mnem_pos = mnemonic_search(inst[0]);
        }
        else {
            printf("Error --- \n");
            break;
        }
    }

    fclose(input);

    return 0;
}

int sym_search(char sym[10]) {
    for(int i = 0; i < stp; i++) {
        if(!strcmp(symbol[i].symbol, sym)) return i;
    }
    return -1;
}

int mnemonic_search(char mnemonic[10]) {
    for(int i = 0; i < 18; i++) {
        if(!strcmp(mottab[i].mnemonic, mnemonic)) return i;
    }
    return -1;
}

int lit_update(char lit[10]) {
    int flag = 0;
    
    for(int i = 0; i < ltp; i++) {
        if(!strcmp(littab[i].name, lit)) {
            flag = 1;
            return i+1;
            break;
        }
    }
    
    if(flag) {
        littab[ltp].sr_no = ltp;
        strcpy(littab[ltp].name, lit);
        ltp++;
        return ltp;
    }
}

void sym_update(int stp, char value[10]) {
    symbol[stp].sr_no = stp + 1;
    
    if(inst[1] == "EQU") symbol[stp].add = evaluate(inst[2]);
    else symbol[stp].add = lc;
    
    strcpy(symbol[stp].symbol, value);
    
    if(strcmp(inst[1], "DS")) symbol[stp].var.length = atoi(inst[2]);
    else if(strcmp(inst[1], "DC")) strcpy(symbol[stp].var.value, inst[2]);
}

void ltorg_allocation() {
    for(int i = pooltab[ptp]; i < ltp; i++) {
        littab[i].add = lc;
        lc++;
    }
    ptp++;
    pooltab[ptp] = ltp;
    printf("(AD, 03)\n");
}

int evaluate(char exp[10]) {
    char op1[10], op2[10];
    int i = 0, op = 1, j = 0;
    
    for(; exp[i] != '+' && exp[i] != '-' && exp[i] != '\0'; i++) op1[i] = exp[i];
    
    if(exp[i] == '-') op = -1;
    else if(exp[i] == '\0') {
        if(isdigit(op1[0])) return atoi(op1);
        else return symbol[sym_search(op1)].add;
    }
    op1[i] = '\0'; i++;
    
    for(; exp[i] != '\0'; i++, j++) op2[j] = exp[i];
    op2[j] = '\0';

    return symbol[sym_search(op1)].add + op*atoi(op2);
}

int is_digit(char exp[10]) {
    if(strcmp(exp, "AREG") == 0) return 1;
    else if(strcmp(exp, "BREG") == 0) return 2;
    else if(strcmp(exp, "CREG") == 0) return 3;
    else if(strcmp(exp, "DREG") == 0) return 4;

    return -1;
}
