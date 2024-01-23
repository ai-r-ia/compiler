#include "whole_include.h"

const long long mod = 1e9 + 9;

HashTable init_table()
{
    HashTable tb = (HashTable)malloc(sizeof(hash_table));
    tb->count = 0;
    return tb;
}

HashNode init_node(String key, int value)
{
    HashNode node = (HashNode)malloc(sizeof(hash_node));
    node->key = key;
    node->value = value;
}

long long get_hash(String str)
{
    int n = len(str);
    long long pref_hash = {str->text[0] - 'a' + 1};
    for (int i = 1; i < n; i++)
    {
        pref_hash = (pref_hash * 53 + (str->text[i] - 'a' + 1)) % mod;
    }
    return pref_hash;
}

void insert_item(HashTable tb, String key, int value)
{
    HashNode node = init_node(key, value);
    int hash_value = get_hash(key) % 58; // maxsize of table = 58

    if (tb->items[hash_value] == NULL)
    {
        tb->items[hash_value] = initialize_vector(HASHNODE);
    }

    push_back(tb->items[hash_value], node);
}

int get_value(HashTable tb, String key)
{
    int hash_value = get_hash(key) % 58;
    if (tb->items[hash_value] == NULL)
    {
        error("No entry with given key.");
        exit(1);
    }
    int size = tb->items[hash_value]->size;
    for (int i = 0; i < size; i++)
    {
        // if (((Vector)(tb->items[hash_value])->data)[i].data == key){
        //     return (tb->items[hash_value]->data)[i].value;
        // }
    }
}