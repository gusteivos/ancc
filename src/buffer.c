#include "buffer.h"

buffer_t *new_buffer(size_t capacity)
{

    buffer_t *buffer = (buffer_t *)malloc(sizeof(buffer_t));

    if (buffer == NULL)
    {

        return NULL;

    }

    buffer->items = (char *)malloc(sizeof(char) * capacity);

    if (buffer->items == NULL)
    {

        free(buffer);

        return NULL;

    }

    buffer->capacity = capacity;

    buffer->count = 0;

    return buffer;

}

int buffer_append(buffer_t *buffer, size_t count, char *items);
int buffer_truncate(buffer_t *buffer, size_t, char *items);

int buffer_push(buffer_t *buffer, char item);
int buffer_pop(buffer_t *buffer, char *item);

void free_buffer(buffer_t *buffer)
{

    if (buffer == NULL)
    {

        return;

    }

    if (buffer->items != NULL)
    {

        free(buffer);

    }

    free(buffer);

}
