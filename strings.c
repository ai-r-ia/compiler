#include "strings.h"

// private

void _initialise(char *ref, size_t start, size_t end)
{
    for (int i = start; i < end; i++)
    {
        ref[i] = '\0';
    }
}

// public functions
String init_str()
{
    String str = (String)malloc(sizeof(struct string));
    str->n = 0;
    str->pos = 0;
    str->text = NULL;

    return str;
}

String buildString(char *a)
{
    size_t n = 0;
    String str = init_str();
    while (a[n] != '\0')
    {
        append(str->text, a[n]);
        n++;
    }
    str->n = n;
    return str;
}

void append(String str, char val)
{

    if (str->text == NULL || str->n == 0)
    {
        str->text = (char *)malloc(sizeof(char) * STRING_INC); // initialize size check
    }
    else if (str->pos >= str->n - 1)
    {
        str->text = (char *)realloc(str->text, sizeof(char) * (str->n + STRING_INC));
    }

    _initialise(str->text, str->n, str->n + STRING_INC);

    str->text[str->pos++] = val;
    str->n += STRING_INC;
}

size_t len(String str)
{
    return str->pos;
}

String add(String a, String b)
{
    // if(a==NULL && b!= NULL) return b;      //return new string
    // if(b==NULL && a!= NULL) return a;

    String str = init_str();
    str->n = a->n + b->n;

    str->text = (char *)malloc(sizeof(char) * str->n);
    str->text = a->text; // should take care of '/0'
    str->pos = a->pos;

    for (int i = 0; i < b->pos; i++)
    {
        append(str->text, b->text[i]);
    }
    // str->pos = str->n -1;
    return str;
}

// compares lengths and letters
int compare(String a, String b)
{
    if (a == NULL && b == NULL)
        return 0;
    if (a != NULL && b == NULL)
        return 1;
    if (a == NULL && b != NULL)
        return -1;

    if (len(a) > len(b))
        return 1;
    if (len(a) < len(b))
        return 1;

    size_t size = len(a) > len(b) ? len(b) : len(a);

    for (int i = 0; i < size; i++)
    {
        if (a->text[i] > b->text[i])
            return 1;
        if (a->text[i] < b->text[i])
            return -1;
    }

    return 0;
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
        for (int i = 0; i < len(source); i++)
        {
            append(destination, source->text[i]);
        }
        return destination;
    }

    destination->n = source->n;
    destination->text = (char *)malloc(sizeof(char) * destination->n);
    destination->pos = 0;

    _initialise(destination->text, 0, destination->n);

    int i = 0;
    while (i < source->n)
    {
        destination->text[destination->pos++] = source->text[i++];
    }

    return destination;
}

String toCapital(String a)
{
    for (int i = 0; i < a->n; i++)
    {
        char c = a->text[i];
        if (c >= 'a' && c <= 'z')
            a->text[i] = 'A' - 'a' + c;
    }
    return a;
}

String toSmall(String a)
{
    for (int i = 0; i < a->n; i++)
    {
        char c = a->text[i];
        if (c >= 'A' && c <= 'Z')
            a->text[i] = 'A' - 'a' - c;
    }
    return a;
}
