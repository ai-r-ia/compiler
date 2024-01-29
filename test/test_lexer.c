#include "test_lexer.h"

void test_lexer()
{
    // Note: run the file from the test folder to avoid errors. Running from lexer.c or ../ directory will cause errors.
    Lexer lexer = init_lexer("test.txt");

    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n", lexer->buff2);
}