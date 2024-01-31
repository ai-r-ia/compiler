#include "../whole_include.h"

void test_hash_table()
{
    info("testing HASH TABLE");
    
    HashTable table = init_table();
    int len = sizeof(keyword_token_value) / sizeof(int);

    for(int i = 0; i<len; i++){
        insert_item(table, buildString(keyword_type_list[i]), keyword_token_value[i]);
    }

    int ind = 3;
    int value = get_value(table, buildString(keyword_type_list[ind]));

    if (value != keyword_token_value[ind]){
        error("Incorrect value.1");
        exit(-1);
    }

    ind = rand() % len;
    value = get_value(table, buildString(keyword_type_list[ind]));

    if (value != keyword_token_value[ind])
    {
        error("Incorrect value.2");
        exit(-1);
    }

     ind = rand() % len;
     value = get_value(table, buildString(keyword_type_list[ind]));

    if (value != keyword_token_value[ind])
    {
        error("Incorrect value.3");
        exit(-1);
    }

    ind = rand() % len;
    value = get_value(table, buildString(keyword_type_list[ind]));

    if (value != keyword_token_value[ind])
    {
        error("Incorrect value.4");
        exit(-1);
    }

    value = get_value(table, buildString("kaiwalya"));

    if (value != -1)
    {
        error("bhagwan aagye.");
        exit(-1);
    }

    success("HASH TABLE tested successfully");
}
