#include "whole_include.h"

const long long mod = 1e9 + 9;

HashTable init_table()
{
    HashTable tb = (HashTable)malloc(sizeof(hash_table));
    tb->items = init_vector(VECTOR);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        push_back(tb->items, init_vector(HASHNODE));
    }

    tb->count = 0;
    return tb;
}

HashNode init_node(String key, int value)
{
    HashNode node = (HashNode)malloc(sizeof(hash_node));
    node->key = key;
    node->value = value;
}

int get_hash(String str)
{
    int n = len(str);
    long long pref_hash = {str->text[0] - 'a' + 1};
    for (int i = 1; i < n; i++)
    {
        pref_hash = (pref_hash * 53 + (str->text[i] - 'a' + 1)) % mod;
    }
    return abs(pref_hash);
}

HashNode _find(Vector vec, String key)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        HashNode node = get(vec, i);
        if (compare(node->key, key))
            return node;
    }
    return NULL;
}

void insert_item(HashTable tb, String key, int value)
{
    HashNode node = init_node(key, value);
    int hash_value = get_hash(key) % TABLE_SIZE;

    Vector row = get(tb->items, hash_value);

    HashNode nd = _find(row, key);
    if (nd)
        nd->value = node->value;
    else
    {
        push_back(row, node);
        tb->count++;
    }
}

int get_value(HashTable tb, String key)
{
    int hash_value = get_hash(key) % TABLE_SIZE;
    Vector row = get(tb->items, hash_value);
    HashNode node = _find(row, key);

    if (node)
        return node->value;
    return -1; // values in hashTable should be positive
}