/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
#ifndef UTILS
#define UTILS

#include "strings.h"
#include "lexical_token.h"
#include "symbol_table.h"
#include "vectors.h"
#include "rules.h"
#include "tree.h"

char rand_char();
int *rand_int_ptr();
char *rand_char_ptr();
String rand_string();
Token rand_token();
SymbolNode rand_symbol_node();
TreeNode rand_tree_node();
Rule rand_rule();
Vector rand_vector(enum DATATYPE type);
void *get_randomizer(enum DATATYPE type);
#endif