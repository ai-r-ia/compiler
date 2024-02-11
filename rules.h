#ifndef RULES
#define RULES

#include "lexical_token.h"
#include "vectors.h"
#include "stdio.h"

#define  GRAMMAR_LENGTH 1000

enum GrammarTokenKind
{
    E,
    A,
    T,
    B,
    F,

    // Do not belong to non terminals
    TERMINAL,
    INVALID_GTOK,
    EOF_GTOK
};

static char *grammarTokenKindString[] =
    {
        "E",
        "A",
        "T",
        "B",
        "F",

        // Not non terminals
        "Terminal",
        "INVALID_GTOK",
        "EOF_GTOK"};

typedef struct grammar *Grammar;
struct grammar
{
    char *filename;
    Vector rules;
} grammar;

typedef struct rule *Rule;
struct rule
{
    Token NT;          // non terminal
    Vector derivables; // rhs of rule
} rule;

Rule init_rule(Token NT);

Grammar init_grammar(char *filename);

void printRule(Rule rule);

// private functions

void _loadGrammar(Grammar grammar);

int _getNonTerminal(String nonTerminal);

#endif