#ifndef HASHDEF
#define HASHDEF

#include "strings.h"
#include "lexical_tokenDef.h"
#include "vectors.h"

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

#endif