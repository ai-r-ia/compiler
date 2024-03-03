#include "whole_include.h"
#include "test/test.h"
#include "driver.h"

int main(int argc, char** args)
{
    *args = "test";

    if (strcmp(*args, "test") == 0)
    {
        testAll();
        return 0;
    }
    else {
        driver();
    }
    printf("not testing\n");
    return 0;
}