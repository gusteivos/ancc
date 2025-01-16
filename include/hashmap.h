
#ifndef HASHMAP_H
#define HASHMAP_H

#include "ancc.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include "hashfunc.h"

typedef struct hashmap_entry_s
{

    size_t key_size;

    void *key;

    uint32_t hash;

    void *value;

} hashmap_entry_t;

typedef struct hashmap_s
{

    hashmap_entry_t *entrys;

    size_t capacity;

    Ihashfunc_t hashfunc;

} hashmap_t;

hashmap_t *new_hashmap(
    size_t capacity,
    Ihashfunc_t hashfunc
    );

int hashmap_get_entry(
    hashmap_t *map,
    size_t key_size,
    void *key,
    hashmap_entry_t **entry
    );

int hashmap_put(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void *value
    );

int hashmap_get(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void **value
    );

int hashmap_remove(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void **value
    );

void free_hashmap(
    hashmap_t *map
    );

#endif/*HASHMAP_H*/
