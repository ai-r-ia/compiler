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
enum dataType
{
    INT,
    CHAR,
    STRING,
};

typedef struct _vector
{
    int vectorType;
    void *data;
    size_t n;
    size_t pos;
} vector;

vector *iVector(int vectorType);

void enqueue(vector *vector, void *data);

void *get(vector *vector, size_t index);

void put(vector *vector, size_t index, void *data);

void push_back(vector *vec, void *data);

bool contains(vector *vec, void *data);

vector *copy_vector(vector *destination, vector *source);

size_t size(vector *vector);

void removeAt(vector *vector, size_t index);

// void *pop_back(vector *vector);

void *copy_data(void *destination, void *source, int type);

void clear(vector* vector);
// for internal workings

void _malloc_vec(vector *vector, size_t size);

void _realloc_vec(vector *vector, size_t new_size);

void *_get(vector *vector, size_t index);

bool _checkEqual(void *a, void *b, int vectorType);

void _put(vector *vector, size_t index, void *data);

void *_copy_data(void *destination, void *source, int type);

#endif