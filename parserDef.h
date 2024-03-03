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

static char *keyword_syn_token_list[] = {
    "TK_COMMENT",
    "TK_END", // check
    "TK_WHILE",
    "TK_UNION",
    "TK_DEFINETYPE",
    "TK_TYPE",
    "TK_MAIN",
    "TK_ENDWHILE", // check
    "TK_IF",
    "TK_CALL",
    "TK_RECORD",
    "TK_CL",
    "TK_SEM",
    "TK_ENDIF",
};

#endif