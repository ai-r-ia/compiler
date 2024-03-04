/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/

#ifndef STRINGSDEF
#define STRINGSDEF

#include <stddef.h>
static int STRING_INC = 10;


// struct for storing strings for lexemes
typedef struct string *String;
struct string
{
    char *text;
    size_t memory_size; // available memory
    size_t size;        // filled length
} extern string;

#endif