#include "test_vector.h"
#define MIN_SIZE 1000

// create a wrapper for all the tests in the module.
void test_vector()
{
    // test_vector_int_all_operations();
    // info("_________________________________\n");
    // test_vector_char_all_operations();
    // info("_________________________________\n");
    // // test_vector_int_ptr_all_operations();
    // // info("_________________________________\n");
    // // test_vector_char_ptr_all_operations();

    // test_vector_string_all_operations();
    // info("_________________________________\n");
    // test_vector_token_all_operations();
    // info("_________________________________\n");
    // test_vector_hash_node_all_operations();
    info("_________________________________\n");
    test_vector_of_vector_all_operations();
}

void test_vector_int_all_operations()
{
    info("Testing for INT\n");
    Vector vec = initialize_vector(INT);

    int not_in_vec = rand();
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    int in_vec;

    for (int i = 0; i < MIN_SIZE; i++)
    {
        int rand_val = rand();
        while (rand_val == not_in_vec)
        {
            rand_val = rand();
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    int get_value = *((int *)get(vec, index));

    if (get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    int c = rand();
    push_back(vec, &c);

    if (c != *((int *)pop_back(vec)))
    {
        error("Error in pop_back().");
        exit(1);
    }

    int next = *((int *)get(vec, index + 1));
    removeAt(vec, index);
    int curr = *((int *)get(vec, index));

    if (curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand();
    push_back(vec, &c);

    success("INT vector tested succesfullly.");
}

void test_vector_char_all_operations()
{
    info("Testing for CHAR\n");
    Vector vec = initialize_vector(CHAR);

    char not_in_vec = rand_char(); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    char in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        char rand_val = rand_char(); // TODO:
        while (rand_val == not_in_vec)
        {
            rand_val = rand_char(); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    char get_value = *((char *)get(vec, index)); // TODO:

    if (get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    char c = rand_char(); // TODO:
    push_back(vec, &c);

    if (c != *((char *)pop_back(vec))) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    char next = *((char *)get(vec, index + 1)); // TODO:
    removeAt(vec, index);
    char curr = *((char *)get(vec, index)); // TODO:

    if (curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_char(); // TODO:
    push_back(vec, &c);

    success("CHAR vector tested succesfullly."); // TODO:
}

void test_vector_int_ptr_all_operations()
{
    info("Testing for INT_PTR\n");
    Vector vec = initialize_vector(INT_PTR); // TODO:

    int *not_in_vec = rand_int_ptr(); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    int *in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        int *rand_val = rand_int_ptr(); // TODO:
        while (rand_val == not_in_vec)
        {
            rand_val = rand_int_ptr(); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    int *get_value = *((int **)get(vec, index)); // TODO:

    if (get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    int *c = rand_int_ptr(); // TODO:
    push_back(vec, &c);

    if (c != *((int **)pop_back(vec))) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    int *next = *((int **)get(vec, index + 1)); // TODO:
    removeAt(vec, index);
    int *curr = *((int **)get(vec, index)); // TODO:

    if (curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_int_ptr(); // TODO:
    push_back(vec, &c);

    success("INT_PTR vector tested succesfullly."); // TODO:
}

void test_vector_char_ptr_all_operations()
{
    info("Testing for CHAR_PTR\n");
    Vector vec = initialize_vector(CHAR_PTR);

    char *not_in_vec = rand_char_ptr(); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    char *in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        char *rand_val = rand_char_ptr(); // TODO:
        while (rand_val == not_in_vec)
        {
            rand_val = rand_char_ptr(); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    char *get_value = *((char **)get(vec, index)); // TODO:

    if (get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    char *c = rand_char_ptr(); // TODO:
    push_back(vec, &c);

    if (c != *((char **)pop_back(vec))) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    char *next = *((char **)get(vec, index + 1)); // TODO:
    removeAt(vec, index);
    char *curr = *((char **)get(vec, index)); // TODO:

    if (curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_char_ptr(); // TODO:
    push_back(vec, &c);

    success("CHAR_PTR vector tested succesfullly."); // TODO:
}

void test_vector_string_all_operations()
{
    info("Testing for STRING\n");
    Vector vec = initialize_vector(STRING);

    String not_in_vec = rand_string(); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    String in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        String rand_val = rand_string(); // TODO:
        while (compare(rand_val, not_in_vec))
        {
            rand_val = rand_string(); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        // printf("%s\n", rand_val->text);
        push_back(vec, rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }
    String get_value = ((String)get(vec, index)); // TODO:

    if (!compare(get_value, in_vec))
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    String c = rand_string(); // TODO:
    push_back(vec, c);

    if (!compare(c, ((String)pop_back(vec)))) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    String next = ((String)get(vec, index + 1)); // TODO:
    String next_val = NULL;
    next_val = copy_string(next_val, next);
    // for (int i = 0; i < vec->size; i++)
    // {
    //     puts(((String)get(vec, i))->text);
    // }
    removeAt(vec, index);
    // info("breakkk");
    // for (int i = 0; i < vec->size; i++)
    // {
    //     puts(((String)get(vec, i))->text);
    // }

    String curr = ((String)get(vec, index)); // TODO:

    if (!compare(curr, next_val))
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_string(); // TODO:
    push_back(vec, c);

    success("STRING vector tested succesfullly."); // TODO:
}

void test_vector_token_all_operations()
{
    info("Testing for TOKEN\n");
    Vector vec = initialize_vector(TOKEN);

    Token not_in_vec = rand_token(); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    Token in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        Token rand_val = rand_token(); // TODO:
        while (rand_val->type == not_in_vec->type)
        {
            rand_val = rand_token(); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        // printf("%s\n", rand_val->text);
        push_back(vec, rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }
    Token get_value = ((Token)get(vec, index)); // TODO:

    if (get_value->type != in_vec->type)
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    Token c = rand_token(); // TODO:
    push_back(vec, c);

    if (c->type != ((Token)pop_back(vec))->type) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    Token next = ((Token)get(vec, index + 1)); // TODO:
    Token next_val = init_Token(next->type, next->value, next->line_num, next->char_num);

    // for (int i = 0; i < vec->size; i++)
    // {
    //     puts(((String)get(vec, i))->text);
    // }
    removeAt(vec, index);
    // info("breakkk");
    // for (int i = 0; i < vec->size; i++)
    // {
    //     puts(((String)get(vec, i))->text);
    // }

    Token curr = ((Token)get(vec, index)); // TODO:

    if (curr->type != next_val->type)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_token(); // TODO:
    push_back(vec, c);

    success("TOKEN vector tested succesfullly."); // TODO:
}

void test_vector_hash_node_all_operations()
{
    info("Testing for HASHNODE\n");
    Vector vec = initialize_vector(HASHNODE);

    HashNode not_in_vec = rand_hash_node(); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    HashNode in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        HashNode rand_val = rand_hash_node(); // TODO:
        while (rand_val->value == not_in_vec->value)
        {
            rand_val = rand_hash_node(); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        // printf("%s\n", rand_val->text);
        push_back(vec, rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }
    HashNode get_value = ((HashNode)get(vec, index)); // TODO:

    if (get_value->value != in_vec->value)
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    HashNode c = rand_hash_node(); // TODO:
    push_back(vec, c);

    if (c->value != ((HashNode)pop_back(vec))->value) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    HashNode next = ((HashNode)get(vec, index + 1)); // TODO:
    HashNode next_val = init_node(next->key, next->value);

    // for (int i = 0; i < vec->size; i++)
    // {
    //     puts(((String)get(vec, i))->text);
    // }
    removeAt(vec, index);
    // info("breakkk");
    // for (int i = 0; i < vec->size; i++)
    // {
    //     puts(((String)get(vec, i))->text);
    // }

    HashNode curr = ((HashNode)get(vec, index)); // TODO:

    if (curr->value != next_val->value)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_hash_node(); // TODO:
    push_back(vec, c);

    success("HASH NODE vector tested succesfullly."); // TODO:
}

void test_vector_of_vector_all_operations()
{
    info("Testing for VECTOR\n");
    Vector vec = initialize_vector(VECTOR);

    Vector not_in_vec = rand_vector(HASHNODE); // TODO:
    size_t index = rand() % MIN_SIZE;
    if (index == (MIN_SIZE - 1))
        index--;
    Vector in_vec; // TODO:

    for (int i = 0; i < MIN_SIZE; i++)
    {
        Vector rand_val = rand_vector(HASHNODE); // TODO:
        while (rand_val->size == not_in_vec->size) //all vecs of diff sizes
        {
            rand_val = rand_vector(HASHNODE); // TODO:
        }
        if (i == index)
        {
            in_vec = rand_val;
        }
        // printf("%s\n", rand_val->text);
        push_back(vec, rand_val);
    }

    if (vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }
    Vector get_value = ((Vector)get(vec, index)); // TODO:

    if (!checkEqual(get_value, in_vec))
    {
        error("Error in get().");
        exit(1);
    }

    if (contains(vec, not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if (!contains(vec, get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL, vec);

    if (!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    Vector c = rand_vector(HASHNODE); // TODO:
    push_back(vec, c);

    if (!checkEqual(c, (Vector)pop_back(vec))) // TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    Vector next = ((Vector)get(vec, index + 1)); // TODO:
    Vector next_val = initialize_vector(HASHNODE);
    next_val = copy_vector(next_val, next);

    // for (int i = 0; i < vec->size; i++)
    // {
    //     for (int j = 0; j < ((Vector)get(vec, i))->size; j++)
    //         puts(((HashNode)(get(((Vector)get(vec, i)),j)))->key);
    // }
    removeAt(vec, index);
    // info("breakkk");
    // for (int i = 0; i < vec->size; i++)
    // {
    //     for (int j = 0; j < ((Vector)get(vec, i))->size; j++)
    //         puts(((HashNode)(get(((Vector)get(vec, i)), j)))->key);
    // }

    Vector curr = ((Vector)get(vec, index)); // TODO:

    if (!checkEqual(curr, next_val))
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if (vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_vector(HASHNODE); // TODO:
    push_back(vec, c);

    success("VECTOR vector tested succesfullly."); // TODO:
}
