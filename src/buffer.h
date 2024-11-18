
#ifndef BUFFER_H
#define BUFFER_H

#include "ancc.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

typedef struct buffer_s
{
    char *items;
    size_t capacity;
    size_t count;
} buffer_t;

buffer_t *new_buffer(size_t capacity);

int buffer_append(buffer_t *buffer, size_t, char *);
int buffer_truncate(buffer_t *buffer, size_t, char *);
int buffer_push(buffer_t *buffer, char item);
int buffer_pop(buffer_t *buffer, char *item);

void free_buffer(buffer_t *buffer);

#endif