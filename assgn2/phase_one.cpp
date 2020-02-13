#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct  MOTTAB {
        char mnemonic[10];
        int code;
        char class[5];
        int operands;
} MOTTAB;

int sym_search(char);
int mnem_search(char );
int sym_update(int, char[]);

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

typedef struct SYMTAB {
    int sr_no;
    char symbol[10];
    int add;
    int length;
} SYMTAB;

struct LITTAB {
    int sr_no;
    char name[10];
    int add;
    struct LITTAB *next;
} LITTAB;

//Initialization
FILE *input;
SYMTAB symbol[20];

int lc = 0, ptp = 0, rc = 0, stp = 0;
int pooltab[20] = {0};

int main() {
    input = fopen("input.txt", "r");
    char line_buf[20], inst[4][20];
    pooltab[0] = 1;

    while(fgets(line_buf,sizeof line_buf,input) != NULL) {
        int count = 0;
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
                printf("\n%s\n", inst[count-1]);
            }
            else i++;
        }
    }
    if(mnem_search(inst[1]) != -1) {
        int pos = sym_search(inst[])
    }

    fclose(input);

    return 0;
}

FILE *input;
SYMTAB symbol[20];

int lc = 0, ptp = 1, rc = 0, stp = 0;
int pooltab[20] = {0};

int sym_search(char lib[10]) {
    for(int i=0; i<stp; i++) {
        if(!strcmp(symbol[i].symbol, sym)) return i;
    return -1;
    }
}

int mnem_search(char mnem[18]) {
    for(int i=0; i<18; i++) {
        if(!strcmp(MOTTAB.mnemonic, mnem)) return i;
    }
    return -1;
}

void sym_update(int stp, char value[10]) {
    symbol[stp].sr_no = stp + 1;
    symbol[stp].add = lc;
    strcpy(symbol[stp].symbol, value);
    if(strcmp(inst[1], "DS"))
        symbol[stp].var.length = atoi(inst[2]);
    else if(strcmp(inst[1], "DC"))
        strcpy(symbol[stp].var.value, inst[2]);
}