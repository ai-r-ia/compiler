#include "test_lexer.h"

void test_lexer()
{
    info("testing LEXER");
    // Note: run the file from the test folder to avoid errors. Running from lexer.c or ../ directory will cause errors.
    Lexer lexer = init_lexer("test.txt");

    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 2;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 1;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 2;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 1;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 2;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 1;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 2;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 1;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);
    lexer->BUFF_NUM = 2;
    _readFile(lexer);
    printf("buff1 : %s\n", lexer->buff1);
    printf("buff2 : %s\n\n", lexer->buff2);

    success("LEXER tested successfully.");
}