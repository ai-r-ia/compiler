#include "whole_include.h"

char rand_char()
{
    char rand_c = (char)(rand()%126 +1);
    return rand_c;
}

int* rand_int_ptr()
{
    int rand_i = rand();
    return &rand_i;
}

char* rand_char_ptr()
{
    char rand_c = rand_char();
    return &rand_c;
}