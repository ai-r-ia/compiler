/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
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
} extern symbol_node;

typedef struct symbol_table *SymbolTable;
struct symbol_table
{
    Vector items; // vector of vector of hash_nodes
    int count;
} extern symbol_table;

SymbolTable init_table();

SymbolNode init_node(String key, Token value);

void insert_item(SymbolTable tb, String key, Token value);

Token get_value(SymbolTable tb, String key);

int get_hash(String str);

void printSymbolTable(SymbolTable tb);

// private

SymbolNode _find(Vector vec, String key);

#endif