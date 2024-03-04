/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
#ifndef VECTORDEF
#define VECTORDEF

#include <stddef.h>

static size_t VECTOR_INC = 1;
static int STRING_SIZE = 1000;

enum DATATYPE
{
    INT,
    CHAR,
    STRING,
    INT_PTR,
    CHAR_PTR,
    TOKEN,
    SYMBOLNODE,
    RULE,
    VECTOR,
    TREENODE
};

static char *data_type_map[] = {
    "INT",
    "CHAR",
    "STRING",
    "INT_PTR",
    "CHAR_PTR",
    "TOKEN",
    "SYMBOLNODE",
    "RULE",
    "VECTOR",
};

/*
 A struct called vector is defined which performs actions akin to arrays but
additional flexibility of assuming different types such as those declared
in the enum DATATYPE.

The functions performed on vectors are described in vectors.h*/

typedef struct vector *Vector;
struct vector
{
    enum DATATYPE DATATYPE; // the DATATYPE from list of enums above
    void *data;             // array of elements of type DATATYPE
    size_t memory_size;     // size of space allocated
    size_t size;            // space filled with data entries
};
#endif