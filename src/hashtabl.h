
#ifndef HASHTABL_H
#define HASHTABL_H

#include "ancc.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
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

    size_t entrys_size;

    hashtable_entry_t *entrys;

    Ihashfunc_t hashfunc;

} hashtable_t;

hashtable_t *new_hashtable(
    size_t size,
    Ihashfunc_t hashfunc
    );

int hashtable_put(
    hashtable_t *map,
    size_t key_size,
    void *key,
    void *value
    );

int hashtable_exists(
    hashtable_t *map,
    size_t key_size,
    void *key
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
