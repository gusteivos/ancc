#include "hashmap.h"

hashmap_t *new_hashmap(
    size_t capacity,
    Ihashfunc_t hashfunc
    )
{

    if (
        capacity == 0 ||
        hashfunc == NULL
        )
    {

        return NULL;

    }

    hashmap_t *map = (hashmap_t *)malloc(sizeof(hashmap_t));

    if (map == NULL)
    {

        return NULL;

    }

    map->entrys = (hashmap_entry_t *)malloc(sizeof(hashmap_entry_t) * capacity);

    if (map->entrys == NULL)
    {

        free(map);

        return NULL;

    }

    map->capacity = capacity;

    size_t i = 0;

    for ( ; i < map->capacity; i++)
    {

        hashmap_entry_t *entry = &map->entrys[i];

        entry->key_size = 0;

        entry->key = NULL;

        entry->hash = 0x00000000;

        entry->value = NULL;

    }

    map->hashfunc = hashfunc;

    return map;

}

STATIC
int hashmap_use_hashfunc(
    hashmap_t *map,
    size_t key_size,
    void *key,
    uint32_t *hash
    )
{

    if (
        map == NULL ||
        key_size == 0 ||
        key == NULL ||
        hash == NULL
        )
    {

        return EINVAL;

    }

    if (map->hashfunc == NULL)
    {

        return ENODEV;

    }

    *hash = map->hashfunc(key_size, key);

    return 0;

}

int hashmap_get_entry(
    hashmap_t *map,
    size_t key_size,
    void *key,
    hashmap_entry_t **entry
    )
{

    if (
        entry == NULL
        )
    {

        return EINVAL;

    }

    uint32_t hash = 0x00000000;

    int q = hashmap_use_hashfunc(
        map,
        key_size,
        key,
        &hash
        );

    if (q != 0)
    {

        return q;

    }

    size_t i = 0;

    for ( ; i < map->capacity; i++)
    {

        size_t entry_index = ((size_t)hash + i) % map->capacity;

        hashmap_entry_t *current_entry = &map->entrys[entry_index];

        if (
            current_entry->key_size != 0 &&
            current_entry->key != NULL
            )
        {

            if (
                current_entry->hash == hash &&
                current_entry->key_size == key_size &&
                memcmp(current_entry->key, key, current_entry->key_size) == 0
                )
            {

                *entry = current_entry;

                return 0;

            }

        }

    }

    return ENOENT;

}

int hashmap_put(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void *value
    )
{

    uint32_t hash = 0x00000000;

    int q = hashmap_use_hashfunc(map, key_size, key, &hash);

    if (q != 0)
    {

        return q;

    }

    size_t i = 0;

    for (; i < map->capacity; i++)
    {

        size_t entry_index = ((size_t)hash + i) % map->capacity;

        hashmap_entry_t *entry_at_index = &map->entrys[entry_index];

        if (
            entry_at_index->key_size != 0 &&
            entry_at_index->key != NULL
            )
        {

            if (
                entry_at_index->hash == hash &&
                entry_at_index->key_size == key_size &&
                memcmp(entry_at_index->key, key, entry_at_index->key_size) == 0
                )
            {

                return EEXIST;

            }

        }
        else
        {

            entry_at_index->key = malloc(key_size);

            if (entry_at_index->key == NULL)
            {

                return EFAULT;

            }

            memcpy(entry_at_index->key, key, key_size);

            entry_at_index->key_size = key_size;

            entry_at_index->hash = hash;

            entry_at_index->value = value;

            return 0;

        }

    }

    return ENOMEM;

}

int hashmap_get(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void **value
    )
{

    hashmap_entry_t *entry = NULL;

    int q = hashmap_get_entry(map, key_size, key, &entry);

    if (q != 0)
    {

        return q;

    }

    *value = entry->value;

    return 0;

}

int hashmap_remove(
    hashmap_t *map,
    size_t key_size,
    void *key,
    void **value
    )
{

    hashmap_entry_t *entry = NULL;

    int q = hashmap_get_entry(map, key_size, key, &entry);

    if (q != 0)
    {

        return q;

    }

    if (value == NULL)
    {

        *value = entry->value;

    }

    entry->key_size = 0;

    free(entry->key);

    entry->key = NULL;

    entry->hash = 0x00000000;

    entry->value = NULL;

    return 0;

}

void free_hashmap(
    hashmap_t *map
    )
{

    if (
        map == NULL
        )
    {

        return;

    }

    size_t i = 0;

    for ( ; i < map->capacity; i++)
    {

        hashmap_entry_t *entry = &map->entrys[i];

        if (entry->key != NULL)
        {

            free(entry->key);

        }

    }

    free(map->entrys);

    free(map);

}
