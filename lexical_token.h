#ifndef LEXER_TOKEN
#define LEXER_TOKEN

#include "whole_include.h"

enum TOKEN_TYPE
{
    // keywords
    INTEGER,
    REAL,
    BOOLEAN,
    OF,
    ARRAY,
    START,
    END,
    DECLARE,
    MODULE,
    DRIVER,
    PROGRAM,
    GET_VALUE,
    PRINT,
    USE,
    WITH,
    PARAMETERS,
    TAKES,
    INPUT,
    RETURNS,
    FOR,
    IN,
    SWITCH,
    CASE,
    BREAK,
    DEFAULT,
    WHILE,

    // variable token
    ID,
    NUM,
    RNUM,
    AND,
    OR,
    TRUE,
    FALSE,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LT,
    LE,
    GE,
    GT,
    EQ,
    NE,
    DEF,
    ENDDEF,
    DRIVERDEF,
    DRIVERENDDEF,
    COLON,
    RANGEOP,
    SEMICOL,
    COMMA,
    ASSIGNOP,
    SQBO,
    SQBC,
    BO,
    BC,
    COMMENTMARK,

    // added
    TK_ILLEGAL,
};

static char *token_type_list[] = {
    // keywords
    "INTEGER",
    "REAL",
    "BOOLEAN",
    "OF",
    "ARRAY",
    "START",
    "END",
    "DECLARE",
    "MODULE",
    "DRIVER",
    "PROGRAM",
    "GET_VALUE",
    "PRINT",
    "USE",
    "WITH",
    "PARAMETERS",
    "TAKES",
    "INPUT",
    "RETURNS",
    "FOR",
    "IN",
    "SWITCH",
    "CASE",
    "BREAK",
    "DEFAULT",
    "WHILE",

    // variable token
    "ID",
    "NUM",
    "RNUM",
    "AND",
    "OR",
    "TRUE",
    "FALSE",
    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "LT",
    "LE",
    "GE",
    "GT",
    "EQ",
    "NE",
    "DEF",
    "ENDDEF",
    "DRIVERDEF",
    "DRIVERENDDEF",
    "COLON",
    "RANGEOP",
    "SEMICOL",
    "COMMA",
    "ASSIGNOP",
    "SQBO",
    "SQBC",
    "BO",
    "BC",
    "COMMENTMARK",

    // added
    "TK_ILLEGAL",
};

typedef struct token *Token;
struct token
{
    enum TOKEN_TYPE type;
    String str;
    size_t line_num;
    size_t char_num;
    // void* value; //TODO: optional (post conversion) or use stoi/stof
};

bool checkIfArithmeticOperator(int lexicalToken);

Token init_Token(int kind, String valueString, int lineNumber, int charNumber);

Token copy_token(Token destination, Token source);

#endif