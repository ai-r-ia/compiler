/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/

#ifndef LEXERDEF
#define LEXERDEF

static int BUFFER_SIZE = 512;

typedef struct lexer *Lexer;
struct lexer
{
    int BUFF_NUM;
    FILE *fp;
    char *filename;
    char curr_char; // current character
    char *buff1;
    char *buff2;
    int fwd_ptr;
    int lineNumber, charNumber, prevLineChar;
};

#endif