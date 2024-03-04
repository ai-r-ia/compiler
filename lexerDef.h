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