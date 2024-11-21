#include "buffer.h"

buffer_t *new_buffer(size_t capacity)
{

    if (
        capacity == 0
        )
    {

        return NULL;

    }

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

int buffer_append(buffer_t *buffer, size_t count, char *items)
{

    if (buffer == NULL || count == 0 || items == NULL)
    {

        return EINVAL;

    }

    size_t new_count = buffer->count + count;

    if (new_count > buffer->capacity)
    {

       char *new_items = guarantees_realloc(
        buffer->items,
        sizeof(char) * buffer->capacity,
        sizeof(char) * new_count
        );

        if (new_items == NULL)
        {

            return ENOMEM;

        }

        buffer->capacity = new_count;

    }

    memcpy(&buffer->items[buffer->count], items, sizeof(char) * count);

    buffer->count = new_count;

    return 0;

}

int buffer_truncate(buffer_t *buffer, size_t count, char *items)
{

    if (buffer == NULL || count == 0 || items == NULL)
    {

        return EINVAL;

    }

    if (buffer->count < count)
    {

        return ERANGE;

    }

    size_t new_count = buffer->count - count;

    memcpy(items, &buffer->items[new_count], sizeof(char) * count);

    buffer->count = new_count;

    return 0;

}

int buffer_push(buffer_t *buffer, char item)
{

    return buffer_append(buffer, sizeof(item), &item);

}

int buffer_pop(buffer_t *buffer, char *item)
{

    return buffer_truncate(buffer, sizeof(*item), item);

}

int buffer_peek(buffer_t *buffer, char *item)
{

    if (
        buffer == NULL ||
        item == NULL
        )
    {

        return EINVAL;

    }

    if (buffer->count < sizeof(char))
    {

        return ERANGE;

    }

    *item = buffer->items[buffer->count - sizeof(char)];

    return 0;

}

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
