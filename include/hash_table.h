#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct hash_table_entry {
    // The actual hash value.
    unsigned int hash;
    // Arbitrary data in key and value.
    void *key;
    void *value;
    // A hash_table_entry is basically a Linked List.
    // This points to the next linked entry.
    struct hash_table_entry *next;
} hash_table_entry;

typedef struct {
    // Compare function to use.
    bool (*compare)(void *, void *);
    // Hashing function to use.
    unsigned int (*hash)(void *);
    // Array of entries (buckets).
    hash_table_entry **buckets;
    // Number of buckets in the **buckets above.
    int buckets_count;
    // Number of entries in the table.
    int entries_count;
} hash_table;

hash_table *hash_table_new();

bool hash_table_put(hash_table *ht, void *key, void *value);
void *hash_table_get(hash_table *ht, void *key);
hash_table_entry *hash_table_get_entry(hash_table *ht, void *key);

bool hash_table_int_compare(void *a, void *b);
unsigned int hash_table_int_hash(void *a);

#endif
