#ifndef HASH
#define HASH

#include "lexical_token.h"
#include "vectors.h"
#include "vectorDef.h"

// #include "whole_include.h"

#define TABLE_SIZE 1000

typedef struct hash_node *HashNode;
struct hash_node
{
    String key;
    int value; // token type
} hash_node;

typedef struct hash_table *HashTable;
struct hash_table
{
    Vector items; // vector of vector of hash_nodes
    int count;
} hash_table;

HashTable init_table();

HashNode init_node(String key, int value);

void insert_item(HashTable tb, String key, int value);

// void remove_itme

int get_value(HashTable tb, String key);

int get_hash(String str);

// private

HashNode _find(Vector vec, String key);

#endif