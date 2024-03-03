#ifndef HASH
#define HASH

#include "lexical_token.h"
#include "vectors.h"
#include "vectorDef.h"

// #include "whole_include.h"

#define TABLE_SIZE 100

typedef struct symbol_node *SymbolNode;
struct symbol_node
{
    String key;
    Token value; // token type
} symbol_node;

typedef struct symbol_table *SymbolTable;
struct symbol_table
{
    Vector items; // vector of vector of hash_nodes
    int count;
} symbol_table;

SymbolTable init_table();

SymbolNode init_node(String key, Token value);

void insert_item(SymbolTable tb, String key, Token value);

Token get_value(SymbolTable tb, String key);

int get_hash(String str);

void printSymbolTable(SymbolTable tb);

// private

SymbolNode _find(Vector vec, String key);

#endif