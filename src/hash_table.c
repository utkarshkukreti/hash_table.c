#include "../include/hash_table.h"

hash_table *hash_table_new() {
    hash_table *a = malloc(sizeof(hash_table));

    a->compare = NULL;
    a->hash = NULL;
    a->buckets = NULL;
    a->buckets_count = 0;
    a->entries_count = 0;

    return a;
}
