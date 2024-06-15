/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#include "whole_include.h"

const long long mod = 1e9 + 9;

SymbolTable init_table()
{
    SymbolTable tb = (SymbolTable)malloc(sizeof(symbol_table));
    tb->items = init_vector(VECTOR);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        push_back(tb->items, init_vector(SYMBOLNODE));
    }

    tb->count = 0;
    return tb;
}

SymbolNode init_node(String key, Token value)
{
    SymbolNode node = (SymbolNode)malloc(sizeof(symbol_node));
    node->key = key;
    node->value = value;
    return node;
}

int get_hash(String str)
{
    int n = str->size;
    long long pref_hash = {str->text[0] - 'a' + 1};
    for (int i = 1; i < n; i++)
    {
        pref_hash = (pref_hash * 53 + (str->text[i] - 'a' + 1)) % mod;
    }
    return llabs(pref_hash);
}

SymbolNode _find(Vector vec, String key)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        SymbolNode node = get(vec, i);
        if (compare(node->key, key))
            return node;
    }
    return NULL;
}

void insert_item(SymbolTable tb, String key, Token value)
{
    SymbolNode node = init_node(key, value);
    int hash_value = get_hash(key) % TABLE_SIZE;

    Vector row = get(tb->items, hash_value);

    SymbolNode nd = _find(row, key);
    if (nd)
        nd->value = copy_token(nd->value, node->value);
    else
    {
        push_back(row, node);
        tb->count++;
    }
}

Token get_value(SymbolTable tb, String key)
{
    int hash_value = get_hash(key) % TABLE_SIZE;
    Vector row = get(tb->items, hash_value);
    SymbolNode node = _find(row, key);

    if (node)
        return node->value;
    return init_token(TK_ILLEGAL, char_to_string("TK_ILLEGAL"), "TK_ILLEGAL", 0, 0);
}

void printSymbolTable(SymbolTable tb)
{
    printf("SYMBOL TABLE\n");
    for (int i = 0; i < tb->items->size; i++)
    {
        Vector row = get(tb->items, i);

        for (int j = 0; j < row->size; j++)
        {
            SymbolNode item = get(row, j);
            printf("Lexeme: %20s  Token: %s\n", item->key->text, token_type_list[item->value->type]);
        }
    }
}