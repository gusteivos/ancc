#include "vector.h"

vector_t *new_vector(size_t capacity)
{

    if (
        capacity == 0
        )
    {

        return NULL;

    }

    vector_t *vector = (vector_t *)malloc(sizeof(vector_t));

    if (vector == NULL)
    {

        return NULL;

    }

    vector->items = (void **)malloc(sizeof(void *) * capacity);

    if (vector->items == NULL)
    {

        free(vector);

        return NULL;

    }

    vector->capacity = capacity;

    vector->count = 0;

    return vector;

}

int vector_push(vector_t *vector, void *item)
{

    if (
        vector == NULL ||
        item == NULL
        )
    {

        return EINVAL;

    }

    size_t new_count = vector->count + 1;

    if (new_count > vector->capacity)
    {

        char *new_items = guarantees_realloc(
        vector->items,
        sizeof(void *) * vector->capacity,
        sizeof(void *) * new_count
        );

        if (new_items == NULL)
        {

            return ENOMEM;

        }

        vector->capacity = new_count;

    }

    vector->items[vector->count] = item;

    vector->count = new_count;

    return 0;

}

int vector_pop(vector_t *vector, void **item)
{

    if (
        vector == NULL ||
        item == NULL
        )
    {

        return EINVAL;

    }

    if (vector->count < 1)
    {

        return ERANGE;

    }

    *item = vector->items[--vector->count];

    return 0;

}

int vector_peak(vector_t *vector, void **item)
{

    if (
        vector == NULL ||
        item == NULL
        )
    {

        return EINVAL;

    }

    if (vector->count < 1)
    {

        return ERANGE;

    }

    *item = vector->items[vector->count - 1];

    return 0;

}

void free_vector(vector_t *vector)
{

    if (
        vector == NULL
        )
    {

        return;

    }

    if (vector->items != NULL)
    {

        free(vector->items);

    }

    free(vector);

}
