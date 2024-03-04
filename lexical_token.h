/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#ifndef LEXER_TOKEN
#define LEXER_TOKEN

// #include "whole_include.h"
#include <stdbool.h>
#include "strings.h"
#include "lexical_tokenDef.h"

bool checkIfArithmeticOperator(int lexicalToken); // TODO: REMOVE:

Token init_token(int type, String lexeme_str, void *value, int lineNumber, int charNumber);

Token copy_token(Token destination, Token source);
#endif