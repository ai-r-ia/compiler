/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#include "whole_include.h"

bool checkIfArithmeticOperator(int lexicalToken)
{
    return lexicalToken == TK_AND || lexicalToken == TK_DIV || lexicalToken == TK_PLUS || lexicalToken == TK_MINUS || lexicalToken == TK_MUL || lexicalToken == TK_OR;
}

Token init_token(int kind, String valueString, void *value, int lineNumber, int charNumber)
{
    Token token = (Token)malloc(sizeof(struct token));
    token->char_num = charNumber;
    token->line_num = lineNumber;
    token->lexeme_str = valueString;
    token->type = kind;
    token->lexeme_value = value;
    token->error_msg = (char *)malloc(sizeof(char) * 300);
    return token;
}
Token copy_token(Token destination, Token source)
{
    if (source == NULL)
    {
        destination = NULL;
        return NULL;
    }

    if (destination == NULL)
    {
        destination = init_token(TK_ILLEGAL, NULL, 0, 0, 0);
        destination->lexeme_str = NULL;
        // return destination;
    }

    destination->type = source->type;
    destination->char_num = source->char_num;
    destination->line_num = source->line_num;
    destination->lexeme_str = copy_string(destination->lexeme_str, source->lexeme_str);

    return destination;
}