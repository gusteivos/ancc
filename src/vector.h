
#ifndef VECTOR_H
#define VECTOR_H

#include "ancc.h"

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

typedef struct vector_s
{

    void **items;

    size_t capacity;

    size_t count;

} vector_t;

vector_t *new_vector(size_t capacity);

int vector_push(vector_t *vector, void *item);

int vector_pop(vector_t *vector, void **item);

int vector_peak(vector_t *vector, void **item);

void free_vector(vector_t *vector);

#endif/*VECTOR_H*/
