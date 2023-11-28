#ifndef STRINGS
#define STRINGS

#include <stddef.h>

static int STRING_INC = 10;

typedef struct String
{
    char *text;
    size_t n;
    size_t pos;
} string;

string *iString();

string *buildString(char *a);

void append(string *str, char val);

size_t len(string *str);

string *add(string *a, string *b);

int compare(string *a, string *b);

string* copy_string(string* destination, string* source);

string* toCapital(string* a);

string *toSmall(string *a);

// For internal workings

void _initialise(char *ref, size_t start, size_t end);

#endif