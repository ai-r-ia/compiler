#include <vectors.c>
#include <vectors.h>
void test_vector_int_all_operations(); // Test pop, push, remove, initialise, copy, etc specifically for int type.
void test_vector_string_all_operations();

void test_vector();

void test_vector_int_all_operations()
{
    Vector vec = initialize_vector(INT);
    printf(vec->DATATYPE);
}


// create a wrapper for all the tests in the module.
void test_vector() {
    test_vector_int_all_operations();
    test_vector_string_all_operations();
}
