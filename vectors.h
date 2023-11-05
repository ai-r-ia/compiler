#ifndef VECTORS
#define VECTORS

#include <stdbool.h>
#include <stddef.h>

static size_t VECTOR_INC = 10;
static int STRING_SIZE = 1000;

// All data types supported by vector
// Remember:
// Add _O for user defined objects to add vector support
// Also add the switch case for new vectorType in
// _malloc_vec , _realloc_vec _put and _get
enum DATATYPE
{
    INT,
    CHAR,
    STRING
};

typedef  struct vector* Vector; 
struct vector
{
    enum DATATYPE DATATYPE;
    void* data;
    size_t size;
    size_t next_index;
};

// vector *iVector(int vectorType);

Vector initialize_vector(enum DATATYPE DATATYPE);

// void enqueue(vector *vector, void *data);

void* get(Vector vec, size_t ind);

void put(Vector vec, size_t ind, void *value);

void push_back(Vector vec, void* value);

bool contains(Vector vec, void *data);

// vector *copy_vector(vector *destination, vector *source);

size_t size(Vector vec);

void removeAt(Vector vec, size_t ind);

void pop_back(Vector vec);

void *copy_data(void *destination, void *source, int type);

void clear(Vector vec);

// for internal workings

void _malloc_vector(Vector vec, size_t size);

void _realloc_vector(Vector vec, size_t size);

// void *_get(vector *vector, size_t index);

bool _checkEqual(void *a, void *b, enum DATATYPE DATATYPE);

// void _put(vector *vector, size_t index, void *data);

// void *_copy_data(void *destination, void *source, int type);

#endif