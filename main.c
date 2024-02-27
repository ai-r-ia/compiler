#include "whole_include.h"
#include "test/test.h"

int main(int argc, char** args)
{
    *args = "test";

    if (strcmp(*args, "test") == 0)
    {
        testAll();
        return 0;
    }
    printf("not testing\n");
    return 0;
}