
#ifndef HASHTABL_H
#define HASHTABL_H

#include "ancc.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include "hashfunc.h"

typedef struct hashtable_entry_s
{

    size_t key_size;

    void *key;

    uint32_t hash;

    void *value;

    struct hashtable_entry_s *next;

} hashtable_entry_t;

typedef struct hashtable_s
{

    hashtable_entry_t **entrys;

    size_t capacity;

    Ihashfunc_t hashfunc;

} hashtable_t;

hashtable_t *new_hashtable(
    size_t capacity,
    Ihashfunc_t hashfunc
    );

int hashtable_get_entry(
    hashtable_t *table,
    size_t key_size,
    void *key,
    uint32_t *hash,
    size_t *index,
    hashtable_entry_t **previous_entry,
    hashtable_entry_t **entry
    );

int hashtable_put(
    hashtable_t *map,
    size_t key_size,
    void *key,
    void *value
    );

int hashtable_get(
    hashtable_t *map,
    size_t key_size,
    void *key,
    void **value
    );

int hashtable_remove(
    hashtable_t *map,
    size_t key_size,
    void *key,
    void **value
    );

void free_hashtable(hashtable_t *map);

#endif/*HASHTABL_H*/
