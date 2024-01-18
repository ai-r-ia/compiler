#include "strings.h"

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
    while(a[n] != '\0')
    {
        append(str->text, a[n]);
        n++;
    }
    str->n = n;
    return str;
}

void append(String str, char val)
{
    
    str->text;

}

size_t len(String str);

String add(String a, String b);

int compare(String a, String b);

String copy_string(String destination, String source);

String toCapital(String a);

String toSmall(String a);

// For internal workings

void _initialise(char *ref, size_t start, size_t end);
