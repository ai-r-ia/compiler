#ifndef PARSEDEF
#define PARSEDEF

#include "tree.h"
#include "vectors.h"
#include "lexer.h"
#include "lexical_token.h"
#include "rules.h"

typedef struct parser *Parser;
struct parser
{
    size_t position;
    Token currentNode;
    Lexer lexer;
    Grammar grammar;
    Vector stack;
    bool noError;

} parser;

#endif