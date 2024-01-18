#ifndef STRINGS
#define STRINGS

#include "whole_include.h"

static int STRING_INC = 10;

typedef struct string *String;
struct string
{
    char *text;
    size_t n;      //available memory
    size_t pos;    //filled length
} string;

String init_str();

String buildString(char *a);

void append(String str, char val);

size_t len(String str);

String add(String a, String b);

int compare(String a, String b);

String copy_string(String destination, String source);

String toCapital(String a);

String toSmall(String a);

// For internal workings

void _initialise(char *ref, size_t start, size_t end);

#endif