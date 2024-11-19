#include "hashmap.h"

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
