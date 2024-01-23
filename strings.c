#include "whole_include.h"

// private

void _initialise(char *ref, size_t start, size_t end)
{
    for (int i = start; i < end; i++)
    {
        ref[i] = '\0';
    }
    // info("added");
}

// public functions
String init_str()
{
    String str = (String)malloc(sizeof(struct string));
    str->memory_size = 0;
    str->size = 0;
    str->text = NULL;

    return str;
}

String buildString(char *a)
{
    size_t n = 0;
    String str = init_str();
    while (a[n] != '\0')
    {
        append(str, a[n]);
        n++;
    }
    str->memory_size = n;
    return str;
}

void append(String str, char val)
{
    // info("append called");
    if (str->text == NULL || str->memory_size == 0)
    {
        if (str->memory_size == 0)
            str->memory_size = 2;
        str->text = (char *)malloc(sizeof(char) * str->memory_size); // initialize size check
        _initialise(str->text, 0, str->memory_size);
    }
    else if (str->size >= str->memory_size - 1)
    {
        str->text = (char *)realloc(str->text, sizeof(char) * (str->memory_size + STRING_INC));
        _initialise(str->text, str->memory_size, str->memory_size + STRING_INC);
        str->memory_size += STRING_INC;
    }

    str->text[str->size++] = val;
}

size_t len(String str)
{
    return str->size;
}

String add(String a, String b)
{
    // if(a==NULL && b!= NULL) return b;      //return new string
    // if(b==NULL && a!= NULL) return a;

    String str = init_str();
    str->memory_size = a->memory_size + b->memory_size;

    str->text = (char *)malloc(sizeof(char) * str->memory_size);
    str->text = a->text; // should take care of '/0'
    str->size = a->size;

    for (int i = 0; i < b->size; i++)
    {
        append(str, b->text[i]);
    }
    // str->pos = str->n -1;
    return str;
}

// compares lengths and letters
int compare(String a, String b)
{
    // puts(a->text);
    // puts(b->text);
    // info("in comp");
    if (a == NULL && b == NULL)
        return 1;
    if (a == NULL || b == NULL)
        return 0;

    if (len(a) != len(b))
        return 0;

    size_t size = len(a) > len(b) ? len(b) : len(a);

    for (int i = 0; i < size; i++)
    {
        if (a->text[i] != b->text[i])
            return 0;
    }

    return 1;
}

String copy_string(String destination, String source)
{
    if (source == NULL)
    {
        destination = NULL;
        return destination;
    }

    if (destination == NULL)
    {
        destination = init_str();
        // for (int i = 0; i < len(source); i++)
        // {
        //     append(destination, source->text[i]);
        // }
        // return destination;
    }

    destination->memory_size = source->memory_size;
    destination->text = (char *)malloc(sizeof(char) * destination->memory_size);
    destination->size = 0;

    _initialise(destination->text, 0, destination->memory_size);

    int i = 0;
    while (i < source->memory_size)
    {
        destination->text[destination->size++] = source->text[i++];
    }
    destination->size--;
    return destination;
}

String toCapital(String a)
{
    for (int i = 0; i < a->memory_size; i++)
    {
        char c = a->text[i];
        if (c >= 'a' && c <= 'z')
            a->text[i] = 'A' - 'a' + c;
    }
    return a;
}

String toSmall(String a)
{
    for (int i = 0; i < a->memory_size; i++)
    {
        char c = a->text[i];
        if (c >= 'A' && c <= 'Z')
            a->text[i] = 'A' - 'a' - c;
    }
    return a;
}
