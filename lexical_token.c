#include "whole_include.h"

bool checkIfArithmeticOperator(int lexicalToken)
{
    return lexicalToken == TK_AND || lexicalToken == TK_DIV || lexicalToken == TK_PLUS || lexicalToken == TK_MINUS || lexicalToken == TK_MUL || lexicalToken == TK_OR;
}

Token init_Token(int kind, String valueString, void *value, int lineNumber, int charNumber)
{
    Token token = (Token)malloc(sizeof(struct token));
    token->char_num = charNumber;
    token->line_num = lineNumber;
    token->lexeme_str = valueString;
    token->type = kind;
    token->lexeme_value = value;
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
        destination = init_Token(TK_ILLEGAL, NULL, 0, 0, 0);
        return destination;
    }

    destination->type = source->type;
    destination->char_num = source->char_num;
    destination->line_num = source->line_num;
    destination->lexeme_str = source->lexeme_str; // TODO: use copystring func

    return destination;
}
