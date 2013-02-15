#include "../include/hash_table.h"

static int primes[29];

hash_table *hash_table_new() {
    hash_table *a = malloc(sizeof(hash_table));

    a->compare = NULL;
    a->hash = NULL;
    a->buckets_count = primes[0];
    a->buckets = calloc(sizeof(*a->buckets), a->buckets_count);
    a->entries_count = 0;

    return a;
}

bool hash_table_put(hash_table *ht, void *key, void *value) {
    hash_table_entry *hte;

    // Already exists.
    if((hte = hash_table_get_entry(ht, key)) != NULL) {
        hte->value = value;
    } else {
        // Make sure load is < HASH_TABLE_MAX_LOAD
        hash_table_ensure_load(ht);

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

bool hash_table_ensure_load(hash_table *ht) {
    if(ht->entries_count / ht->buckets_count >= HASH_TABLE_MAX_LOAD) {
        hash_table_entry **old_buckets = ht->buckets;
        int old_buckets_count = ht->buckets_count;

        // Find the next entry in the table
        int i = 0;
        while(primes[i] <= ht->buckets_count) { i++; }
        ht->buckets_count = primes[i];
        ht->buckets = calloc(sizeof(*ht->buckets), ht->buckets_count);
        ht->entries_count = 0;

        // Re-insert all entries
        for(i = 0; i < old_buckets_count; i++) {
            hash_table_entry *ptr = old_buckets[i];
            while(ptr != NULL) {
                hash_table_put(ht, ptr->key, ptr->value);
                ptr = ptr->next;
            }
        }
    }
    return true;
}

// Helpers
bool hash_table_int_compare(void *a, void *b) {
    return *((int *) a) == *((int *) b);
}

unsigned int hash_table_int_hash(void *a) {
    return *((int *) a) >> 2;
}

// List of Prime numbers just over 2 ^ n, for n = 2..30
// Generated with the following Pari/GP code
// for(i = 2, 30, printf("% 11d + %d,\n", 2 ^ i, nextprime(2 ^ i) - 2 ^ i))
static int primes[] = {
              4 + 1,
              8 + 3,
             16 + 1,
             32 + 5,
             64 + 3,
            128 + 3,
            256 + 1,
            512 + 9,
           1024 + 7,
           2048 + 5,
           4096 + 3,
           8192 + 17,
          16384 + 27,
          32768 + 3,
          65536 + 1,
         131072 + 29,
         262144 + 3,
         524288 + 21,
        1048576 + 7,
        2097152 + 17,
        4194304 + 15,
        8388608 + 9,
       16777216 + 43,
       33554432 + 35,
       67108864 + 15,
      134217728 + 29,
      268435456 + 3,
      536870912 + 11,
     1073741824 + 3
};
