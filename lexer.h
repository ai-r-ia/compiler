#ifndef LEXER
#define LEXER

#include <stdio.h>
#include "strings.h"
#include "lexical_token.h"

static int BUFFER_SIZE = 256;

typedef struct lexer *Lexer;
struct lexer
{
    int BUFF_SIZE1; // occupied buffer1
    int BUFF_SIZE2; // occupied buffer2
    int BUFF_NUM;
    FILE *fp;
    char *filename;
    // char curr_char; // current character
    char *buff1;
    char *buff2;
    int buff_begin1;
    int buff_begin2;
    int buffp1;
    int buffp2;
    int lineNumber, charNumber, prevLineChar;
};

// Constructor for Lexer
Lexer init_lexer(char *filename);

// loads lexer buffer with given string
void loadBuffer(Lexer lexer, String data);

// Gives next character in lexer
char getNextCharacter(Lexer lexer);

// Gets the lex token from file
// Also, increments the file pointer
Token lex(Lexer lexer);

// Checks whether word is a keyword or not
// if it is a keyword it gives the appropriate LexicalTokens
int getKeyword(String word);

// Checks whether a character is [a-z] | [A-Z]
bool isChar(char value);

// Checks whether a character is [0-9]
bool isDigit(char value);

// Checks for record type
bool isRecord(char value);

// Checks for union type
bool isUnion(char value);

// Retrieves kind of keyword
int getKeyword(String word);

// Retrieves ID token
Token getID(Lexer lexer, char curr);

// Retrieves NUM / RNUM token
Token getNUM(Lexer lexer, char curr);

// Retrieves Symbol Token
Token getSymbol(Lexer lexer, char curr);

// private functions (internal)

// Opens the File pointer in the lexer
void _openFile(Lexer lexer);

// Reads the contents of the file and stores them in
void _readFile(Lexer lexer);

// Closes the File pointer in the lexer
void _closeFile(Lexer lexer);

#endif