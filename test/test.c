#include "test.h"

void testAll()
{
    // Calls all the wrappers of every module.
    info("testing\n");
    // test_vector();
    // test_hash_table();
    // test_lexer();
    // test_grammar();
    test_parser();
    return;
}