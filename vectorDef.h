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