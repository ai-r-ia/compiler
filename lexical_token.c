#include "lexical_token.h"

bool checkIfArithmeticOperator(int lexicalToken)
{
    return lexicalToken == AND || lexicalToken == DIV || lexicalToken == PLUS || lexicalToken == MINUS || lexicalToken == MUL || lexicalToken == OR;
}

Token init_Token(int kind, String valueString, int lineNumber, int charNumber)
{
    Token token = (Token)malloc(sizeof(struct token));
    token->char_num = charNumber;
    token->line_num = lineNumber;
    token->str = valueString;
    token->type = kind;
    return token;
}

Token copy_token(Token destination, Token source)
{
    if (source == NULL)
    {
        destination == NULL;
        return NULL;
    }

    if (destination == NULL)
    {
        destination = init_Token(TK_ILLEGAL, NULL, 0, 0);
        return destination;
    }

    destination->type = source->type;
    destination->char_num = source->char_num;
    destination->line_num = source->line_num;
    destination->str = source->str; // TODO: use copystring func

    return destination;
}
