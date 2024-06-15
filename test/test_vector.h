#ifndef TEST_VECTORS
#define TEST_VECTORS
// #include "../vectors.h"
#include "../whole_include.h"
#include "../vectors.h"
#include "../lexical_token.h"
#include "../symbol_table.h"
#include "../rules.h"
#include "../strings.h"
#include "../utils.h"
#include "../printers.h"

void test_vector_int_all_operations(); // Test pop, push, remove, initialise, copy, etc specifically for int type.
void test_vector_string_all_operations();
void test_vector_char_all_operations();
void test_vector_char_ptr_all_operations();
void test_vector_int_ptr_all_operations();
void test_vector_string_all_operations();
void test_vector_token_all_operations();
// void test_vector_hash_node_all_operations();
void test_vector_symbol_node_all_operations();
void test_vector_rule_all_operations();
void test_vector_tree_node_all_operations();
void test_vector_of_vector_all_operations();

void test_vector();
#endif