#ifndef UTILS
#define UTILS

// #include "whole_include.h"
#include "strings.h"
#include "lexical_token.h"
#include "hash.h"
#include "vectors.h"

char rand_char();
int *rand_int_ptr();
char *rand_char_ptr();
String rand_string();
Token rand_token();
HashNode rand_hash_node();
Vector rand_vector(enum DATATYPE type);
void *get_randomizer(enum DATATYPE type);
#endif