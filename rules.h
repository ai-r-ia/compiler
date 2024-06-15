/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
#ifndef RULES
#define RULES

#include "lexical_token.h"
#include "vectors.h"
#include "stdio.h"
#include "vectorDef.h"
#include "rulesDef.h"

Rule init_rule(Token NT);

Grammar init_grammar(char *filename);

void printRule(Rule rule);

void printParseTable(Grammar grammar);

void populateFirst(Grammar grammar);

void populateFollow(Grammar grammar);

void populateParseTable(Grammar grammar);

Vector getFirst(Token token, Grammar grammar);

// private functions

void _loadGrammar(Grammar grammar);

int _matchNonTerminal(String nonTerminal);

#endif