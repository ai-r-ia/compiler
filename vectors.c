#include "whole_include.h"

// all private methods begin with "_"(underscore)

Vector init_vector(enum DATATYPE DATATYPE)
{
    Vector vec = (Vector)malloc(sizeof(struct vector));
    _malloc_vector(vec, DATATYPE);
    vec->DATATYPE = DATATYPE;
    vec->size = 0;

    return vec;
}

void *get(Vector vec, size_t ind)
{
    void *value = NULL;
    if (ind >= vec->size || ind < 0)
    {
        printf("Index out of bound\n");
    }
    else
    {
        value = _get(vec, ind);
        // printf("value %d\n", value);
    }
    return value;
}

size_t get_index(Vector vec, void *data)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        if (_checkEqual(get(vec, i), data, vec->DATATYPE))
            return i;
    }
    return vec->size;
}

void put(Vector vec, size_t ind, void *value)
{
    if (ind >= vec->size || ind < 0)
    {
        printf("Index out of bound\n");
    }
    else
    {
        _put(vec, ind, value);
    }
}

void push_back(Vector vec, void *value)
{
    if (vec->size >= vec->memory_size)
    {
        _realloc_vector(vec);
    }

    _put(vec, vec->size, value);

    vec->size++;
    // TODO: internal put ignoring index, in put too
    // NOTE: test this
}

void *pop_back(Vector vec)
{
    void *ret = get(vec, vec->size - 1);
    vec->size--;
    return ret;
}

bool contains(Vector vec, void *data)
{
    if (get_index(vec, data) != vec->size)
        return true;
    return false;
}

void removeAt(Vector vec, size_t ind)
{
    if (ind >= vec->size || ind < 0)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (ind < vec->size - 1)
    {
        for (int i = ind; i < vec->size - 1; i++)
        {
            put(vec, i, get(vec, i + 1));
        }
    }

    vec->size--;
    // NOTE: test this
}

void clear(Vector vec)
{
    vec->size = 0;
}

Vector copy_vector(Vector destination, Vector source)
{
    if (destination == NULL)
    {
        destination = init_vector(source->DATATYPE);
    }

    destination->DATATYPE = source->DATATYPE;
    destination->size = 0;

    for (size_t i = 0; i < source->size; i++)
    {
        push_back(destination, get(source, i));
    }

    return destination;
}

bool checkEqual(Vector a, Vector b)
{
    if ((a->size != b->size) || (a->DATATYPE != b->DATATYPE))
    {
        return false;
    }

    for (int i = 0; i < a->size; i++)
    {
        if (!_checkEqual(get(a, i), get(b, i), a->DATATYPE))
        {
            return false;
        }
    }

    return true;
}

void *find(Vector vec, void *data)
{
    size_t index = get_index(vec, data);
    if(index == vec->size) return NULL;
    return get(vec, index);
}

// for internal use (private)

void _malloc_vector(Vector vec, enum DATATYPE datatype)
{

    switch (datatype)
    {
    case INT:
        vec->data = (int *)malloc(sizeof(int) * VECTOR_INC);
        break;
    case CHAR:
        vec->data = (char *)malloc(sizeof(char) * VECTOR_INC);
        break;
    case INT_PTR:
        vec->data = (int **)malloc(sizeof(int *) * VECTOR_INC);
        break;
    case CHAR_PTR:
        vec->data = (char **)malloc(sizeof(char *) * VECTOR_INC);
        break;
    case STRING:
        vec->data = (String)malloc(sizeof(struct string) * VECTOR_INC);
        break;
    case TOKEN:
        vec->data = (Token)malloc(sizeof(struct token) * VECTOR_INC);
        break;
    case HASHNODE:
        vec->data = (HashNode)malloc(sizeof(struct hash_node) * VECTOR_INC);
        break;
    case VECTOR:
        vec->data = (Vector)malloc(sizeof(struct vector) * VECTOR_INC);
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

    switch (vec->DATATYPE)
    {
    case INT:
        new_size = sizeof(int) * (vec->memory_size + VECTOR_INC);
        break;
    case CHAR:
        new_size = sizeof(char) * (vec->memory_size + VECTOR_INC);
        break;
    case INT_PTR:
        new_size = sizeof(int *) * (vec->memory_size + VECTOR_INC);
        break;
    case CHAR_PTR:
        new_size = sizeof(char *) * (vec->memory_size + VECTOR_INC);
        break;
    case STRING:
        new_size = sizeof(struct string) * (vec->memory_size + VECTOR_INC);
        break;
    case TOKEN:
        new_size = sizeof(struct token) * (vec->memory_size + VECTOR_INC);
        break;
    case HASHNODE:
        new_size = sizeof(struct hash_node) * (vec->memory_size + VECTOR_INC);
        break;
    case VECTOR:
        new_size = sizeof(struct vector) * (vec->memory_size + VECTOR_INC);
        break;
    default:
        break;
    }

    vec->data = realloc(vec->data, new_size);

    vec->memory_size += VECTOR_INC;
}

bool _checkEqual(void *a, void *b, enum DATATYPE DATATYPE)
{
    switch (DATATYPE)
    {
    case INT:
        return *(int *)a == *(int *)b;
    case CHAR:
        return *(char *)a == *(char *)b;
    case INT_PTR:
        return *(int **)a == *(int **)b;
    case CHAR_PTR:
        return *(char **)a == *(char **)b;
    case STRING:
        return (compare((String )a, (String)b));
    case TOKEN:
        return ((Token)a)->type == ((Token)b)->type;
    case HASHNODE:
        return ((HashNode)a)->value == ((HashNode)b)->value;
    case VECTOR:
        return checkEqual((Vector)a, (Vector)b);
    }
}

void _put(Vector vec, size_t index, void *value)
{
    switch (vec->DATATYPE)
    {
    case INT:
        ((int *)vec->data)[index] = *((int *)value);
        break;
    case CHAR:
        ((char *)vec->data)[index] = *((char *)value);
        break;
    case INT_PTR:
        ((int **)vec->data)[index] = *((int **)value);
        break;
    case CHAR_PTR:
        ((char **)vec->data)[index] = *((char **)value);
        break;
    case STRING:
        // puts(((String)value)->text);
        ((String )vec->data)[index] = *((String)value);
        // puts(((String)vec->data)[index].text);
        break;
    case TOKEN:
        ((Token)vec->data)[index] = *((Token)value);
        break;
    case HASHNODE:
        ((HashNode)vec->data)[index] = *((HashNode)value);
        break;
    case VECTOR:
        ((Vector)vec->data)[index] = *((Vector)value);
        break;
    default:
        printf("Error in inserting data in the vector\n");
        break;
    }
}

void *_get(Vector vec, size_t ind)
{
    void *value;
    switch (vec->DATATYPE)
    {
    case INT:
        value = &(((int *)(vec->data))[ind]);
        break;
    case CHAR:
        value = &(((char *)(vec->data))[ind]);
        break;
    case INT_PTR:
        value = &(((int **)(vec->data))[ind]);
        break;
    case CHAR_PTR:
        value = &(((char **)(vec->data))[ind]);
        break;
    case STRING:
        value = &(((String)(vec->data))[ind]);
        // printf("%ld\n", ((String)value)->n);
        // printf("%ld\n", ((String)value)->pos);
        break;
    case TOKEN:
        value = &(((Token)(vec->data))[ind]);
        break;
    case HASHNODE:
        value = &(((HashNode)(vec->data))[ind]);
        break;
    case VECTOR:
        value = &(((Vector)(vec->data))[ind]);
        break;
    default:
        break;
    }

    return value;
}