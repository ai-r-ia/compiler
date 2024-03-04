/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#ifndef LEXER
#define LEXER

#include <stdio.h>
#include "strings.h"
#include "lexical_token.h"

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

// Function to remove comments from a file
void remove_comments(const char *input_filename, const char *output_filename);

// Constructor for Lexer
Lexer init_lexer(char *filename);

// Gives next character in lexer
char getNextCharacter(Lexer lexer);

// retracts the forward pointer in the buffer
void retract(Lexer lexer, String lexeme);

// Gets the lex token from file
Token getNextToken(Lexer lexer);

// check delimiter or comment
bool isDelimiter(char value);

// Checks whether a character is [a-z] | [A-Z]
bool isLetter_a2z_A2Z(char value);

// Checks whether a character is [a-z]
bool isLetter_a2z(char value);

// Checks whether a character is [A-Z]
bool isLetter_A2Z(char value);

// Checks whether a character is [b-d]
bool isLetter_b2d(char value);

// Checks whether a character is [e-z]
bool isLetter_e2z(char value);

// Checks whether a character is [0-9]
bool isDigit_0_9(char value);

// Checks whether a character is [2-7]
bool isDigit_2_7(char value);

// for valid symbols (except [_],[#])
bool isSymbol(char value);

// checks for valid symbol table operator entries
bool isSymbolTableOperator(String str);

// Retrieves kind of keyword
int getKeyword(String word);

// reads until delimiter reached
Token tokenize_function(Lexer lexer, String lexeme, enum TOKEN_TYPE type, bool others);

// Retrieves ID token
Token get_char_tk(Lexer lexer);

// Retrieves NUM / RNUM token
Token get_numeric_tk(Lexer lexer);

// Retrieves Symbol Token
Token get_symbol_tk(Lexer lexer);

// initial state in TK_FIELDID and TK_ID identification branch
Token after_b2d(Lexer lexer, String lexeme);

// final state in TK_FIELDID identification branch
Token get_tk_fieldid(Lexer lexer, String lexeme);

// states in TK_ID identification branch
Token get_tk_id2(Lexer lexer, String lexeme);
Token get_tk_id3(Lexer lexer, String lexeme);

// states in TK_FUNID identification branch
Token get_tk_funid0(Lexer lexer, String lexeme);
Token get_tk_funid1(Lexer lexer, String lexeme);
Token get_tk_funid3(Lexer lexer, String lexeme);

// states in TK_RUID identification branch
Token get_tk_ruid0(Lexer lexer, String lexeme);
Token get_tk_ruid1(Lexer lexer, String lexeme);

// states in TK_RNUM identification branch
Token get_tk_rnum1(Lexer lexer, String lexeme);
Token get_tk_rnum2(Lexer lexer, String lexeme);
Token get_tk_rnum3(Lexer lexer, String lexeme);
Token get_tk_rnum4(Lexer lexer, String lexeme);
Token get_tk_rnum5(Lexer lexer, String lexeme);
Token get_tk_rnum6(Lexer lexer, String lexeme);

// private functions (internal)

// Opens the File pointer in the lexer
void _openFile(Lexer lexer);

// Reads the contents of the file and stores them in
void _readFile(Lexer lexer);

// Closes the File pointer in the lexer
void _closeFile(Lexer lexer);

#endif