#include "vectors.h"

// all private methods begin with "_"(underscore)

Vector initialize_vector(enum DATATYPE DATATYPE)
{
    Vector vec = (Vector)malloc(sizeof(struct vector));
    _malloc_vector(vec, DATATYPE);
    vec->DATATYPE = DATATYPE;
    vec->size = 0;
    
    return vec;
}

void* get(Vector vec, size_t ind)
{
    void* value = NULL;
    if(ind >= vec->size || ind<0)
    {
        printf("Index out of bound\n");
    }
    else{
        switch (vec->DATATYPE) 
        {
        case INT:
            value = &(((int*)(vec->data))[ind]);
            break;
        case CHAR:
            value = &(((char*)(vec->data))[ind]);
            break;
        default:
            break;
        }
        // printf("value %d\n", value);
    }
    return value;
}

size_t get_index(Vector vec, void* data)
{
    // TODO: checkequal, remove switch
    for(size_t i =0; i<vec->size; i++)
    {
        switch(vec->DATATYPE)
        {
            case INT:
                if(*(int*)get(vec, i) == *(int*)data) return i;
                break;
        }
        
    }
    return vec->size;
}

void put(Vector vec, size_t ind, void *value)
{
    if(ind >= vec->size || ind< 0)
    {
        printf("Index out of bound\n");
    }
    else{
        switch(vec->DATATYPE)
        {
            case INT:
                ((int *)vec->data)[ind] = *((int *)value);
                break;
            case CHAR:
                ((char *)vec->data)[ind] = *((char *)value);
                break;
            case STRING:
                // (vec+ind)->data = (string *)value;
                break;
            default:
                printf("Error in inserting data in the vector\n");
                break;
        }
    }
}

void push_back(Vector vec, void* value)
{
    if(vec->size >= vec->memory_size)
    {
        _realloc_vector(vec);
    }
    // TODO: internal put ignoring index, in put too

    switch(vec->DATATYPE)
        {
            case INT:
                ((int *)vec->data)[vec->size] = *((int *)value);
                break;
            case CHAR:
                ((char *)vec->data)[vec->size] = *((char *)value);
                break;
            case STRING:
                // (vec+ind)->data = (string *)value;
                break;
            default:
                printf("Error in inserting data in the vector\n");
                break;
        }

    vec->size++;
}

void* pop_back(Vector vec)
{
    void * ret = get(vec, vec->size-1); 
    vec->size--;
    return ret;
}

bool contains(Vector vec, void *data)
{
    if(get_index(vec, data) != vec->size) return true;
    return false;
}

void removeAt(Vector vec, size_t ind)
{
    int a = 0;
    char c = '0';
    switch(vec->DATATYPE)
    {
        case INT:
            put(vec, ind, &a);
            break;
        case CHAR:
            put(vec, ind, &c); 
            break;

    }
    //TODO: shift all elts, no switch-case, check size
}

void clear(Vector vec)
{
    vec->size = 0;
}


Vector copy_vector(Vector destination, Vector source)
{
    if(destination == NULL)
    {
        destination = initialize_vector(source->DATATYPE);
    }

    destination->DATATYPE = source->DATATYPE;
    destination->size = 0;

    for(size_t i = 0; i<source->size; i++)
    {
        push_back(destination, get(source,i));
    }

    return destination;
}


// for internal use (private)

void _malloc_vector(Vector vec, enum DATATYPE datatype)
{

    switch (datatype)
    {
    case INT:
        vec->data = (int*)malloc(sizeof(int)* VECTOR_INC);
        break;
    case CHAR:
        vec->data = (char*)malloc(sizeof(char)*VECTOR_INC);
        break;
    case STRING:
        // alloc_size = sizeof(char);
        // alloc_size*= STRING_SIZE;
        break;
    default:
        break;
    }
    vec->memory_size = VECTOR_INC;
    // return vec;
}

void _realloc_vector(Vector vec)
{
    size_t new_size;

    switch(vec->DATATYPE)
    {
        case INT:
            new_size = sizeof(int)*(vec->memory_size + VECTOR_INC);
            break;
        case CHAR:
            new_size = sizeof(char)*(vec->memory_size + VECTOR_INC);
            break;
    }
   
    vec->data = realloc(vec->data, new_size);
    
    vec->memory_size += VECTOR_INC;
}

bool _checkEqual(void *a, void *b, enum DATATYPE DATATYPE)
{
    if(DATATYPE == INT)
    {
        return *(int *)a==*(int *)b;
    }
    else if( DATATYPE == CHAR)
    {
        return *(char *)a==*(char *)b;
    }
    else if (DATATYPE == STRING)
    {
    //    int val = strcmp(*(string *)a,*b);
    }
    
}

