#include "test_vector.h"
#define MIN_SIZE 1000

// create a wrapper for all the tests in the module.
void test_vector() {
    test_vector_int_all_operations();
    info("_________________________________\n");
    test_vector_char_all_operations();
    // info("_________________________________\n");
    // test_vector_int_ptr_all_operations();
    // info("_________________________________\n");
    // test_vector_char_ptr_all_operations();
    
    // test_vector_string_all_operations();
}


void test_vector_int_all_operations()
{
    info("Testing for INT\n");
    Vector vec = initialize_vector(INT);

    int not_in_vec = rand();
    size_t index = rand()%MIN_SIZE;
    if(index == (MIN_SIZE-1)) index--;
    int in_vec;

    for(int i = 0; i<MIN_SIZE; i++)
    {
        int rand_val = rand();
        while(rand_val == not_in_vec)
        {
            rand_val = rand();
        }
        if(i==index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if(vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    int get_value = *((int*)get(vec, index));

    if(get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }
    
    if(contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if(!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL,vec);

    if(!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    int c = rand();
    push_back(vec,&c);

    if(c != *((int*)pop_back(vec)))
    {
        error("Error in pop_back().");
        exit(1);
    }

    int next = *((int*)get(vec, index +1));
    removeAt(vec,index);
    int curr = *((int*)get(vec, index ));

    if(curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if(vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand();
    push_back(vec,&c);

    success("INT vector tested succesfullly.");
   }

void test_vector_char_all_operations()
{
    info("Testing for CHAR\n");
    Vector vec = initialize_vector(CHAR);

    char not_in_vec = rand_char(); //TODO:
    size_t index = rand()%MIN_SIZE;
    if(index == (MIN_SIZE-1)) index--;
    char in_vec; //TODO:

    for(int i = 0; i<MIN_SIZE; i++)
    {
        char rand_val = rand_char(); //TODO:
        while(rand_val == not_in_vec)
        {
            rand_val = rand_char(); //TODO:
        }
        if(i==index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if(vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    char get_value = *((char*)get(vec, index)); //TODO:

    if(get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }
    
    if(contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if(!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL,vec);

    if(!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    char c = rand_char(); //TODO:
    push_back(vec,&c);

    if(c != *((char*)pop_back(vec))) //TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    char next = *((char*)get(vec, index +1)); //TODO:
    removeAt(vec,index);
    char curr = *((char*)get(vec, index )); //TODO:

    if(curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if(vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_char(); //TODO:
    push_back(vec,&c);

    success("CHAR vector tested succesfullly."); //TODO:
}

void test_vector_int_ptr_all_operations()
{
    info("Testing for INT_PTR\n");
    Vector vec = initialize_vector(INT_PTR);//TODO:

    int* not_in_vec = rand_int_ptr(); //TODO:
    size_t index = rand()%MIN_SIZE;
    if(index == (MIN_SIZE-1)) index--;
    int* in_vec; //TODO:

    for(int i = 0; i<MIN_SIZE; i++)
    {
        int* rand_val = rand_int_ptr(); //TODO:
        while(rand_val == not_in_vec)
        {
            rand_val = rand_int_ptr(); //TODO:
        }
        if(i==index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if(vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    int* get_value = *((int**)get(vec, index)); //TODO:

    if(get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }
    
    if(contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if(!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL,vec);

    if(!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    int* c = rand_int_ptr(); //TODO:
    push_back(vec,&c);

    if(c != *((int**)pop_back(vec))) //TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    int* next = *((int**)get(vec, index +1)); //TODO:
    removeAt(vec,index);
    int* curr = *((int**)get(vec, index )); //TODO:

    if(curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if(vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_int_ptr(); //TODO:
    push_back(vec,&c);

    success("INT_PTR vector tested succesfullly."); //TODO:
}

void test_vector_char_ptr_all_operations()
{
    info("Testing for CHAR_PTR\n");
    Vector vec = initialize_vector(CHAR_PTR);

    char* not_in_vec = rand_char_ptr(); //TODO:
    size_t index = rand()%MIN_SIZE;
    if(index == (MIN_SIZE-1)) index--;
    char* in_vec; //TODO:

    for(int i = 0; i<MIN_SIZE; i++)
    {
        char* rand_val = rand_char_ptr(); //TODO:
        while(rand_val == not_in_vec)
        {
            rand_val = rand_char_ptr(); //TODO:
        }
        if(i==index)
        {
            in_vec = rand_val;
        }
        push_back(vec, &rand_val);
    }

    if(vec->size != MIN_SIZE)
    {
        error("Size of array inconsistent.");
        exit(1);
    }

    char* get_value = *((char**)get(vec, index)); //TODO:

    if(get_value != in_vec)
    {
        error("Error in get().");
        exit(1);
    }
    
    if(contains(vec, &not_in_vec))
    {
        error("Error in contains(). --negative case");
        exit(1);
    }

    if(!contains(vec, &get_value))
    {
        error("Error in contains(). --positive case");
        exit(1);
    }

    Vector vec2 = copy_vector(NULL,vec);

    if(!checkEqual(vec, vec2))
    {
        error("Error in checkEqual().");
        exit(1);
    }

    char* c = rand_char_ptr(); //TODO:
    push_back(vec,&c);

    if(c != *((char**)pop_back(vec))) //TODO:
    {
        error("Error in pop_back().");
        exit(1);
    }

    char* next = *((char**)get(vec, index +1)); //TODO:
    removeAt(vec,index);
    char* curr = *((char**)get(vec, index )); //TODO:

    if(curr != next)
    {
        error("Error in removeAt().");
        exit(1);
    }

    clear(vec2);

    if(vec2->size != 0)
    {
        error("Error in clear().");
        exit(1);
    }

    c = rand_char_ptr(); //TODO:
    push_back(vec,&c);

    success("CHAR_PTR vector tested succesfullly."); //TODO:
}