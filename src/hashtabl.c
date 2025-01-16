#include "hashtabl.h"

hashtable_t *new_hashtable(size_t capacity, Ihashfunc_t hashfunc)
{

    if (
        capacity == 0 ||
        hashfunc == NULL
        )
    {
        return NULL;
    }

    hashtable_t *table = (hashtable_t *)malloc(sizeof(hashtable_t));

    if (table == NULL)
    {

        return NULL;

    }

    table->entrys = (hashtable_entry_t **)malloc(sizeof(hashtable_entry_t *) * capacity);

    if (table->entrys == NULL)
    {

        free(table);

        return NULL;

    }

    table->capacity = capacity;

    size_t i = 0;

    for ( ; i < table->capacity; i++)
    {

        table->entrys[i] = NULL;

    }

    table->hashfunc = hashfunc;

    return table;

}

STATIC
int hashtable_use_hashfunc(
    hashtable_t *table,
    size_t key_size,
    void *key,
    uint32_t *hash
    )
{

    if (
        table == NULL ||
        key_size == 0 ||
        key == NULL ||
        hash == NULL
        )
    {

        return EINVAL;

    }

    if (table->hashfunc == NULL)
    {

        return ENODEV;

    }

    *hash = table->hashfunc(key_size, key);

    return 0;

}

int hashtable_get_entry(
    hashtable_t *table,
    size_t key_size,
    void *key,
    uint32_t *hash,
    size_t *index,
    hashtable_entry_t **previous_entry,
    hashtable_entry_t **entry
    )
{

    if (
        table == NULL
        )
    {

        return EINVAL;

    }

    uint32_t entry_hash = 0x00000000;

    int q = hashtable_use_hashfunc(table, key_size, key, &entry_hash);

    if (q != 0)
    {

        return q;

    }

    size_t entry_index = (size_t)entry_hash % table->capacity;

    hashtable_entry_t *current_entry = table->entrys[entry_index];

    if (hash != NULL)
    {

        *hash = entry_hash;

    }

    if (index != NULL)
    {

        *index = entry_index;

    }

    while (current_entry != NULL)
    {

        if (
            current_entry->key_size != 0 &&
            current_entry->key != NULL
            )
        {

            if (
                current_entry->hash == entry_hash &&
                current_entry->key_size == key_size &&
                memcmp(current_entry->key, key, current_entry->key_size) == 0
                )
            {

                *entry = current_entry;

                return 0;

            }

        }

        if (previous_entry != NULL)
        {

            *previous_entry = current_entry;

        }

        current_entry = current_entry->next;

    }

    return ENOENT;

}

int hashtable_put(hashtable_t *table, size_t key_size, void *key, void *value)
{

    uint32_t hash = 0x00000000;

    size_t index = 0;

    hashtable_entry_t *previous_entry = NULL;

    hashtable_entry_t *entry = NULL;

    int q = hashtable_get_entry(table, key_size, key, &hash, &index, &previous_entry, &entry);

    if (q == 0)
    {

        return EEXIST;

    }

    if (q != ENOENT)
    {

        return q;

    }

    hashtable_entry_t *new_entry = (hashtable_entry_t *)malloc(sizeof(hashtable_entry_t));

    if (new_entry == NULL)
    {

        return EFAULT;

    }

    new_entry->key = malloc(key_size);

    if (new_entry->key == NULL)
    {

        free(new_entry);

        return EFAULT;

    }

    memcpy(new_entry->key, key, key_size);

    new_entry->key_size = key_size;

    new_entry->hash = hash;

    new_entry->value = value;

    new_entry->next = NULL;

    if (previous_entry == NULL)
    {

        table->entrys[index] = new_entry;

    }
    else
    {

        previous_entry->next = new_entry;

    }

    return 0;

}

int hashtable_get(hashtable_t *table, size_t key_size, void *key, void **value)
{

    if (
        value == NULL
        )
    {

        return  EINVAL;

    }

    hashtable_entry_t *entry = NULL;

    int q = hashtable_get_entry(table, key_size, key, NULL, NULL, NULL, &entry);

    if (q != 0)
    {

        return q;

    }

    *value = entry->value;

    return 0;

}

int hashtable_remove(hashtable_t *table, size_t key_size, void *key, void **value)
{

    size_t index = 0;

    hashtable_entry_t *previous_entry = NULL;

    hashtable_entry_t *entry = NULL;

    int q = hashtable_get_entry(table, key_size, key, NULL, &index, &previous_entry, &entry);

    if (q != 0)
    {

        return q;

    }

    if (value != NULL)
    {

        *value = entry->value;

    }

    if (previous_entry != NULL)
    {

        previous_entry->next = entry->next;

    }
    else
    {

        table->entrys[index] = entry->next;

    }

    free(entry->key);

    free(entry);

    return 0;

}

void free_hashtable(hashtable_t *table)
{

    if (
        table == NULL
        )
    {

        return;

    }

    size_t i = 0;

    for ( ; i < table->capacity; ++i)
    {

        hashtable_entry_t *entry = table->entrys[i];

        while (entry != NULL)
        {

            hashtable_entry_t *next_entry = entry->next;

            free(entry->key);

            free(entry);

            entry = next_entry;

        }

    }

    free(table->entrys);

    free(table);

}
