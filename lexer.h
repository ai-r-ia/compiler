#ifndef LEXER
#define LEXER

#include <stdio.h>
#include "strings.h"
#include "lexical_token.h"

static int BUFFER_SIZE = 256;

typedef struct lexer *Lexer;
struct lexer
{
    int BUFF_SIZE1; // occupied buffer1 //TODO: REMOVE
    int BUFF_SIZE2; // occupied buffer2
    int BUFF_NUM;
    FILE *fp;
    char *filename;
    char curr_char; // current character
    char *buff1;
    char *buff2;
    // int buff_begin1;
    // int buff_begin2;
    int fwd_ptr;
    int buffp1;
    int buffp2;
    int lineNumber, charNumber, prevLineChar;
};

// Constructor for Lexer
Lexer init_lexer(char *filename);

// loads lexer buffer with given string
// void loadBuffer(Lexer lexer, String data);

// Gives next character in lexer
char getNextCharacter(Lexer lexer);

// Gets the lex token from file
// Also, increments the file pointer
Token tokenize(Lexer lexer, bool readNext);

// Checks whether a character is [a-z] | [A-Z]
bool isLetter_a2z_A2Z(char value);

//[a-z]
bool isLetter_a2z(char value);

// [b-d]
bool isLetter_b2d(char value);

// [e-z]
bool isLetter_e2z(char value);

// Checks whether a character is [0-9]
bool isDigit_0_9(char value);

//[2-7]
bool isDigit_2_7(char value);

// for valid symbols (except [_],[#])
bool isSymbol(char value);

// Retrieves kind of keyword
int getKeyword(String word);

// Retrieves ID token
Token get_char_tk(Lexer lexer);

// Retrieves NUM / RNUM token
Token get_numeric_tk(Lexer lexer);

// Retrieves Symbol Token
Token get_symbol_tk(Lexer lexer);

// private functions (internal)

// Opens the File pointer in the lexer
void _openFile(Lexer lexer);

// Reads the contents of the file and stores them in
void _readFile(Lexer lexer);

// Closes the File pointer in the lexer
void _closeFile(Lexer lexer);

// records lexical error
void _lexical_error(Lexer lexer);

/*  states
-1: error
0: start- checks whitespaces and eof
1: get_char_tk ...[a_z] | [_] | [#]
2: get_numeric_tk
3: get_symbol_tk
_____________________________________________
In character based tokens: 13 states
4: if [b-d]
5: if [a |e-z] | [a-z] and check Keyword
6: ret tk_fieldid
7: from 4 accepts [2-7] to transition, loops on [b-d]
8: loops on [2-7]
9: ret tk_id

10: if [_]
11: loops on [a-z|A-Z], check keyword
12: loops on [0-9]
13: ret tk_funid

14: if[#]
15: loops on [a-z]
16: ret tk_ruid
________________________________________________

In digit based tokens: 10 states
17: if [.]
18: ret tk_num
19: if [0-9] after 17
20: if [0-9] after 19
21: if [E]
22: if [+|-]
23: if [0-9] after 22
24: if [0-9] after 23
25: ret tk_rnum
__________________________________________________


*/
#endif