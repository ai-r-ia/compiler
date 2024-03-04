/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
#ifndef STRINGS
#define STRINGS

// #include "whole_include.h"
#include <stddef.h>
#include "stringsDef.h"

String init_str();

String char_to_string(char *a);

void append(String str, char val);

void pop_str(String str);

int compare(String a, String b);

String copy_string(String destination, String source);

// private functions

void _initialise(char *ref, size_t start, size_t end);

#endif