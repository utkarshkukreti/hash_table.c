#include "../include/hash_table.h"

hash_table *hash_table_new() {
    hash_table *a = malloc(sizeof(hash_table));

    a->compare = NULL;
    a->hash = NULL;
    // TODO: No hardcoding. Use a prime number table.
    a->buckets = calloc(sizeof(*a->buckets), 5);
    a->buckets_count = 5;
    a->entries_count = 0;

    return a;
}

bool hash_table_put(hash_table *ht, void *key, void *value) {
    hash_table_entry *hte;

    // Already exists.
    if((hte = hash_table_get_entry(ht, key)) != NULL) {
        hte->value = value;
    } else {
        unsigned int hash = ht->hash(key);
        int bucket = hash % ht->buckets_count;

        hte = malloc(sizeof(hash_table_entry));
        hte->hash = hash;
        hte->key = key;
        hte->value = value;
        hte->next = NULL;

        if(ht->buckets[bucket] == NULL) {
            ht->buckets[bucket] = hte;
        } else {
            hash_table_entry *ptr = ht->buckets[bucket];
            while(ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = hte;
        }
        // This was a new entry, increment entries_count.
        ht->entries_count++;
    }

    return true;
}

void *hash_table_get(hash_table *ht, void *key) {
    hash_table_entry *hte;
    if((hte = hash_table_get_entry(ht, key)) != NULL) {
        return hte->value;
    }
    return NULL;
}

hash_table_entry *hash_table_get_entry(hash_table *ht, void *key) {
    unsigned int hash = ht->hash(key);
    int bucket = hash % ht->buckets_count;

    if(ht->buckets[bucket] == NULL) {
        // There's not even one record in the bucket
        return NULL;
    } else {
        // Loop through the entries, and check
        hash_table_entry *ptr = ht->buckets[bucket];
        while(ptr != NULL) {
            // Check if hash is equal
            if(ptr->hash == hash) {
                // Ok, hash is equal, now run the real compare() function
                if(ht->compare(ptr->key, key) == true) {
                    return ptr;
                }
            }
            ptr = ptr->next;
        }
        return NULL;
    }
}

// Helpers
bool hash_table_int_compare(void *a, void *b) {
    return *((int *) a) == *((int *) b);
}

unsigned int hash_table_int_hash(void *a) {
    return *((int *) a) >> 2;
}
