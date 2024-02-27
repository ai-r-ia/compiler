#include "whole_include.h"

char rand_char()
{
    // char rand_c = (char)(rand() % 126 + 1);
    char rand_c = rand() % (126 - 32 + 1) + 32;
    return rand_c;
}

int *rand_int_ptr()
{
    int static rand_i;
    rand_i = rand();
    return &rand_i;
}

char *rand_char_ptr()
{
    char static rand_c;
    rand_c = rand_char();
    return &rand_c;
}

String rand_string()
{
    String str = init_str();
    size_t len = rand() % 1000;
    // size_t len = 10;
    str->memory_size = len + 1;
    for (int i = 0; i < str->memory_size - 1; i++)
    {
        char c = rand_char();
        append(str, c);
    }
    return str;
}

Token rand_token()
{
    // NOTE: always keep type as tk_fieldid, tk_funid, tk_id, tk_ruid.....update for more
    int type = rand() % 58; //(tk_illegal +1)
    String value = char_to_string(token_type_list[type]);
    Token tk = init_token(type, value, value->text, rand() % 1000, rand() % 1000);
    return tk;
}

HashNode rand_hash_node() // rename
{
    HashNode node = init_node(rand_string(), rand() % 1000);
    return node;
}

Vector rand_vector(enum DATATYPE type)
{
    Vector vec = init_vector(HASHNODE);

    int len = rand() % 10;
    for (int i = 0; i < len; i++)
    {
        void *(*fun)(void) = get_randomizer(type);
        push_back(vec, fun());
    }

    return vec;
}

SymbolNode rand_symbol_node()
{
    String lexeme = rand_string();
    Token tk = rand_token();
    return init_symbol(lexeme, tk);
}

Rule rand_rule()
{
    Token tk = rand_token();
    return init_rule(tk);
}

TreeNode rand_tree_node(){
    Token tk = rand_token();
    return init_treenode(tk);
}

    void *get_randomizer(enum DATATYPE type)
{
    switch (type)
    {
    case INT:
        return &rand;
    case CHAR:
        return &rand_char;
    case TOKEN:
        return &rand_token;
    case STRING:
        return &rand_string;
    case INT_PTR:
        return &rand_int_ptr;
    case CHAR_PTR:
        return &rand_char_ptr;
    case HASHNODE:
        return &rand_hash_node;
    case SYMBOLNODE:
        return &rand_symbol_node;
    default:
        break;
    }
    return 0;
}