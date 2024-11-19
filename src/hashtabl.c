#include "hashtabl.h"

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
