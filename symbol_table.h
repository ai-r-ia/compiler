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
#include "symbol_tableDef.h"

SymbolTable init_table();

SymbolNode init_node(String key, Token value);

void insert_item(SymbolTable tb, String key, Token value);

Token get_value(SymbolTable tb, String key);

int get_hash(String str);

void printSymbolTable(SymbolTable tb);

// private

SymbolNode _find(Vector vec, String key);

#endif