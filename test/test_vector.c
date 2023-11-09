#include "test_vector.h"

void test_vector_int_all_operations()
{
    Vector vec = initialize_vector(INT);
    printf("size: %ld\n", vec->size);

    int a[5] = {5,6,78,3,12};
    push_back(vec, &a[0]);
    push_back(vec, &a[1]);
    push_back(vec, &a[2]);
    push_back(vec, &a[3]);
    push_back(vec, &a[4]);

    int b = 12;
    if(contains(vec, &b))
    {
        printf("yes\n");
    }
    else{
        printf("no\n");
    }

    
    Vector vec2 = copy_vector(NULL,vec);
    int c = 13;
    push_back(vec,&c);
    printf("popped %d\n", *((int*)pop_back(vec)));
    c = 15;
    push_back(vec,&c);
    removeAt(vec,3);
    // clear(vec);
    push_back(vec,&c);

    for(int i = 0; i<vec->size; i++)
    {
        printf("%d ",*((int*)get(vec, i)));

    }
    printf("\n");
    for(int i = 0; i<vec2->size; i++)
    {
        printf("%d ",*((int*)get(vec2, i)));

    }
    printf("\n");
   }

void test_vector_char_all_operations()
{
    Vector vec = initialize_vector(CHAR);
    printf("size: %ld\n", vec->size);

    char a[5] = {'a','b','c','d','e'};
    push_back(vec, &a[0]);
    push_back(vec, &a[1]);
    push_back(vec, &a[2]);
    push_back(vec, &a[3]);
    push_back(vec, &a[4]);


    char b = 'f';
    if(contains(vec, &b))
    {
        printf("yes\n");
    }
    else{
        printf("no\n");
    }

    Vector vec2 = copy_vector(NULL,vec);
    
    char c = 'g';
    push_back(vec,&c);
    printf("popped %c\n", *((char*)pop_back(vec)));
    c = 'h';
    push_back(vec,&c);
    removeAt(vec,3);
    // clear(vec);
    put(vec,4,&c);

    for(int i = 0; i<vec->size; i++)
    {
        printf("%c ",*((char*)get(vec, i)));

    }
    printf("\n");
    for(int i = 0; i<vec2->size; i++)
    {
        printf("%c ",*((char*)get(vec2, i)));

    }
    printf("\n");
    printf("size of vector: %ld\n", vec->size); //should this == nextIndex?
}

// TODO: template test func, RANDOMIZE, store some randoms use to check contains, store popped
// size check, pop, push. get, put, contains--> datatype agnostic, abstract func

// create a wrapper for all the tests in the module.
void test_vector() {
    printf("testing int vector\n");
    test_vector_int_all_operations();
    printf("_________________________________\n");
    printf("testing char vector\n");
    test_vector_char_all_operations();
    // test_vector_string_all_operations();
}
