#include <vectors.h>

typedef  struct vector* Vector; 
struct vector
{
    int dataType;
    void* data;
    int size;
    int next_index;
};

void* malloc_vector(Vector vec)
{
    
    int alloc_size = 0;
    
    switch (vec->dataType)
    {
    case INT:
        alloc_size = sizeof(int);
        break;
    case CHAR:
        alloc_size = sizeof(char);
        break;
    case STRING:
        alloc_size = sizeof(char);
        alloc_size*= STRING_SIZE;
        break;
    default:
        break;
    }
    vec = (void*)malloc(alloc_size* VECTOR_INC);
    vec->size = VECTOR_INC;
    return vec;
}

void* realloc_vector(Vector vec)
{
    
    int alloc_size = 0;
    
    switch (vec->dataType)
    {
    case INT:
        alloc_size = sizeof(int);
        break;
    case CHAR:
        alloc_size = sizeof(char);
        break;
    case STRING:
        alloc_size = sizeof(char);
        alloc_size*= STRING_SIZE;
        break;
    default:
        break;
    }
    int new_size = VECTOR_INC+ vec->size;
    vec = (void*)realloc(vec, alloc_size*new_size);
    vec->size = new_size;
    return vec;
}

void* get(Vector vec, int ind)
{
    void* value = NULL;
    if(ind > vec->size || ind<= vec->size)
    {
        printf("Index out of bound\n");
    }
    else{
        value = (vec+ind)->data;
    }
    return value;
}

void put(Vector vec, int ind, void *value)
{
    if(ind > vec->size || ind<= vec->size)
    {
        printf("Index out of bound\n");
    }
    else{
        (vec+ind)->data = value;
        vec->next_index++;
    }
}

void push_back(Vector vec, void* value)
{
    if(vec->next_index >= vec->size)
    {
        vec = realloc_vector(vec);
    }
    put(vec, vec->next_index, value);
}

void pop_back(Vector vec)
{
    put(vec, vec->next_index -1, NULL);
}

bool contains(Vector vec, void *data)
{
    if(get(vec, data) != NULL) return true;
    return false;
}

void removeAt(Vector vec, int ind)
{
    put(vec, ind, NULL);
}

bool _checkEqual(void *a, void *b, int vectorType)
{
    
}