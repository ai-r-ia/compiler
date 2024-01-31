#include "whole_include.h"

char rand_char()
{
    // char rand_c = (char)(rand() % 126 + 1);
    char rand_c = rand() % (126 - 32 + 1) + 32;
    return rand_c;
}

int *rand_int_ptr()
{
    int rand_i = rand();
    return &rand_i;
}

char *rand_char_ptr()
{
    char rand_c = rand_char();
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
    int type = rand() % 58; //(tk_illegal +1)
    String value = char_to_string(token_type_list[type]);
    Token tk = init_Token(type, value, rand() % 1000, rand() % 1000);
    return tk;
}

HashNode rand_hash_node() // rename
{
    HashNode node = init_node(rand_string(), rand() % 1000);
    return node;
}

Vector rand_vector(enum DATATYPE type)
{
    Vector vec = initialize_vector(HASHNODE);

    int len = rand() % 10;
    for (int i = 0; i < len; i++)
    {
        void* (*fun)(void) = get_randomizer(type);
        push_back(vec, fun());
    }

    return vec;
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
    default:
        break;
    }
}