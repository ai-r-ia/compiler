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

typedef struct vector *Vector;
struct vector
{
    enum DATATYPE DATATYPE;
    void *data;
    size_t memory_size;
    size_t size;
};
#endif