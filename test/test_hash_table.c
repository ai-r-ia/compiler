#include "../whole_include.h"

void test_hash_table()
{
    info("testing HASH TABLE");

    SymbolTable table = init_table();
    int len = sizeof(keyword_token_value) / sizeof(int);

    for (int i = 0; i < len; i++)
    {
        Token tk = init_token(i, char_to_string(keyword_type_list[i]), (keyword_type_list[i]), 0, 0);
        insert_item(table, char_to_string(keyword_type_list[i]), tk);
    }

    int ind = 3;
    // Token tk = init_token(ind, char_to_string(keyword_type_list[ind]), (keyword_type_list[ind]), 0, 0);
    Token value = get_value(table, char_to_string(keyword_type_list[ind]));

    if (value->type != ind)
    {
        error("Incorrect value.1");
        exit(-1);
    }

    ind = rand() % len;
    value = get_value(table, char_to_string(keyword_type_list[ind]));

    if (value->type != ind)
    {
        error("Incorrect value.2");
        exit(-1);
    }

    ind = rand() % len;
    value = get_value(table, char_to_string(keyword_type_list[ind]));

    if (value->type != ind)
    {
        error("Incorrect value.3");
        exit(-1);
    }

    ind = rand() % len;
    value = get_value(table, char_to_string(keyword_type_list[ind]));

    if (value->type != ind)
    {
        error("Incorrect value.4");
        exit(-1);
    }

    value = get_value(table, char_to_string("kaiwalya"));

    if (value->type != TK_ILLEGAL)
    {
        error("Incorrect value.5");
        exit(-1);
    }

    success("HASH TABLE tested successfully");
}
