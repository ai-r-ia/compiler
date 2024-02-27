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
