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