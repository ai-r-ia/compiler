#ifndef SYMBOL
#define SYMBOL

#include "strings.h"
#include "vectors.h"
#include "lexical_token.h"

#define SYMBOL_TABLE_SIZE 1000

typedef struct symbol_node *SymbolNode;
struct symbol_node
{
    String lexeme;
    Token token; // token
} symbol_node;

typedef struct symbol_table *SymbolTable;
struct symbol_table
{
    Vector items; // vector of symbol_nodes
    int count;
} symbol_table;

// initialize symbol_node
void init_symbol(String lexeme, Token token);

// initialize symbol_node
void init_symbol_table();

// insert entry into symbol table
void insert(String lexeme, Token token);

// lookup
SymbolNode search(String lexeme);

#endif