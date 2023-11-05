#include <vectors.h>

// all private methods begin with "_"(underscore)

typedef  struct vector* Vector; 
struct vector
{
    enum DATATYPE DATATYPE;
    void* data;
    size_t size;
    size_t next_index;
};


Vector initialize_vector(enum DATATYPE DATATYPE)
{
    Vector vec;

    switch(DATATYPE)
    {
        case INT:
            vec->DATATYPE = INT;
            vec->size = 0;
            vec->next_index = 0;
            _malloc_vector(vec, VECTOR_INC);
            break;
        case CHAR:
            vec->DATATYPE = CHAR;
            vec->size = 0;
            vec->next_index = 0;
            _malloc_vector(vec, VECTOR_INC);
            break;
        case STRING:
            vec->DATATYPE = STRING;
            vec->size = 0;
            vec->next_index = 0;
            _malloc_vector(vec, VECTOR_INC);
            break;
        default:
            printf("Error in initializing the vector\n");
            break;
    }
    
    return vec;
}

void* get(Vector vec, size_t ind)
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

void put(Vector vec, size_t ind, void *value)
{
    if(ind > vec->size || ind<= vec->size)
    {
        printf("Index out of bound\n");
    }
    else{
        switch(vec->DATATYPE)
        {
            case INT:
                (vec+ind)->data = (int *)value;
                break;
            case CHAR:
                (vec+ind)->data = (char *)value;
                break;
            case STRING:
                // (vec+ind)->data = (string *)value;
                break;
            default:
                printf("Error in inserting data in the vector\n");
                break;
        }
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
    vec->next_index-=2;
}

bool contains(Vector vec, void *data)
{
    if(get(vec, data) != NULL) return true;
    return false;
}

void removeAt(Vector vec, size_t ind)
{
    put(vec, ind, NULL);
}

void clear(Vector vec)
{
    vec->next_index = 0;
}


size_t size(Vector vec)
{
    return vec->size;
}

// for internal use (private)

void _malloc_vector(Vector vec, size_t size)
{
    
    int alloc_size = size/VECTOR_INC;
    if((size % VECTOR_INC)>=1) alloc_size++;
    
    switch (vec->DATATYPE)
    {
    case INT:
        alloc_size = sizeof(int);
        break;
    case CHAR:
        alloc_size = sizeof(char);
        break;
    case STRING:
        // alloc_size = sizeof(char);
        // alloc_size*= STRING_SIZE;
        break;
    default:
        break;
    }
    vec = (void*)malloc(alloc_size* VECTOR_INC);
    vec->size = VECTOR_INC;
}

void _realloc_vector(Vector vec, size_t size)
{
     
    int alloc_size = size/VECTOR_INC;
    if((size % VECTOR_INC)>=1) alloc_size++;
    
    switch (vec->DATATYPE)
    {
    case INT:
        alloc_size = sizeof(int);
        break;
    case CHAR:
        alloc_size = sizeof(char);
        break;
    case STRING:
        // alloc_size = sizeof(char);
        // alloc_size*= STRING_SIZE;
        break;
    default:
        break;
    }
    int new_size = alloc_size*VECTOR_INC+ vec->size;
    vec = (void*)realloc(vec, new_size);
    vec->size = new_size;
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

