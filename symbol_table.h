#ifndef SYMBOL
#define SYMBOL

#include "strings.h"
#include "vectors.h"
#include "lexical_token.h"
#include "vectorDef.h"

#define SYMBOL_TABLE_SIZE 1000

typedef struct symbol_node *SymbolNode;
struct symbol_node
{
    String lexeme;
    Token token; // token
} symbol_node;

// initialize symbol_node
SymbolNode init_symbol(String lexeme, Token token);

// insert entry into symbol table
void insert(Vector vec, String lexeme, Token token);

// lookup
SymbolNode search(String lexeme);

#endif