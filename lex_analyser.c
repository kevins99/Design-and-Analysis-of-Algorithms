#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE_NAME = "./code.txt";
TRN_FILE = "./terminal.txt";
FILE *fp;

typedef struct UST
{
    int sr_no;
    char keyword[5];
    char type;
    int ref;
} UST;

typedef struct LITTAB
{
    int sr_no;
    char literal[10];
} LITTAB;

typedef struct IDNTAB
{
    int sr_no;
    char idn[10];
} IDNTAB;

typedef struct TRNTAB
{
    int sr_no;
    char trm[3];
} TRNTAB;

TRNTAB trn[50];
IDNTAB idn[50];
LITTAB lit[50];

char delimiter[20] = {
    ',',
    ';',
    ' ',
    '(',
    ')',
    '{',
    '}',
};

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

bool isOperator(char *ch)
{
    for (int i = 0; i < sizeof(TRNTAB) / sizeof(trn); i++)
    {
        if (ch == trn[i].trm)
            return true;
    }
    return false;
}

bool isIdentifier(char *ch)
{
    for (int i = 0; i < sizeof(IDNTAB) / sizeof(idn); i++)
    {
        if (ch == idn[i].idn)
            return true;
    }
    return false;
}

void parse_sentence(char *str)
{
    int len = strlen(str);
}

void tokenise(FILE *fp)
{
    fseek(fp, 0, SEEK_CUR);
    char *code = malloc(1000 * sizeof(char));
    while ((char)fgetc(fp) != ';')
    {
        *code++ = (char)fgetc(fp);
    }
    parse_sentence(code);
    fp++;
}

void loadStruct(char *TRN_FILE, char *)
{
    FILE *trn;
    trn = fopen(TRN_FILE, "r+");
}

int main()
{
    fp = fopen(FILE_NAME, "r");

    while (!feof(fp))
    {
        //INSERT LOGIC
        printf("START");
        tokenise(fp);
    }
    fclose(fp);
}