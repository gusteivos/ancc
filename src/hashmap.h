
#ifndef HASHMAP_H
#define HASHMAP_H

#include "ancc.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
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

    size_t entrys_size;

    hashmap_entry_t *entrys;

    Ihashfunc_t hashfunc;

} hashmap_t;

hashmap_t *new_hashmap(
    size_t size,
    Ihashfunc_t hashfunc
    );

int hashmap_put(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void *value
    );

int hashmap_exists(
    hashmap_t *map,
    size_t key_size,
    void *key
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

void free_hashmap(hashmap_t *map);

#endif/*HASHMAP_H*/
