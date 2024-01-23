#ifndef HASH
#define HASH

#include "lexical_token.h"
#include "vectors.h"
// #include "whole_include.h"

typedef struct hash_node *HashNode;
struct hash_node
{
    String key;
    int value; // token type
} hash_node;

typedef struct hash_table *HashTable;
struct hash_table
{
    Vector* items; // vector of vector of hash_nodes
    int count;
} hash_table;

HashTable init_table();

HashNode init_node(String key, int value);

void insert_item(HashTable tb, String key, int value);

int get_value(HashTable tb, String key);

long long get_hash();

#endif