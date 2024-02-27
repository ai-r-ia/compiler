#ifndef VECTORS
#define VECTORS

// #include "whole_include.h"
#include "vectorDef.h"

Vector init_vector(enum DATATYPE DATATYPE);

void *get(Vector vec, size_t ind);

void put(Vector vec, size_t ind, void *value);

void push_back(Vector vec, void *value);

bool contains(Vector vec, void *data);

void removeAt(Vector vec, size_t ind);

bool checkEqual(Vector a, Vector b);

void *pop_back(Vector vec);

void* top(Vector vec);

Vector copy_vector(Vector destination, Vector source);//NOTE: remove

void clear(Vector vec); // NOTE: remove

void *find(Vector vec, void *data);

void printVector(Vector vector);

// private functions

void _malloc_vector(Vector vec, enum DATATYPE DATATYPE);

void _realloc_vector(Vector vec);

bool _checkEqual(void *a, void *b, enum DATATYPE DATATYPE);

void _put(Vector vector, size_t index, void *data);

void *_get(Vector vec, size_t ind);

#endif