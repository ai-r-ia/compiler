/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#include "whole_include.h"
#include "test/test.h"
#include "driver.h"

int main(int argc, char** args)
{
    *args = "test";
    printf("You have entered %d arguments:\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", args[i]);
    }

    if (strcmp(*args, "test") == 0)
    {
        testAll();
        return 0;
    }
    else {
        // driver(*(char**)args[1]);
        driver("t8.txt");
    }
    printf("not testing\n");
    return 0;
}