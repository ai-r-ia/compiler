/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/

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

} extern parser;

static char *keyword_syn_token_list[] = {
    "TK_COMMENT",
    "TK_END",
    "TK_WHILE",
    "TK_UNION",
    "TK_DEFINETYPE",
    "TK_TYPE",
    "TK_MAIN",
    "TK_ENDWHILE",
    "TK_IF",
    "TK_CALL",
    "TK_RECORD",
    "TK_CL",
    "TK_SEM",
    "TK_ENDIF",
    "TK_ENDUNION",
    "TK_RETURN",
    "TK_ENDRECORD",
};

static char *start_keyword_list[] = {
    "TK_WHILE",
    "TK_UNION",
    "TK_DEFINETYPE",
    // "TK_TYPE",
    "TK_MAIN",
    "TK_IF",
    "TK_RECORD",
};

#endif