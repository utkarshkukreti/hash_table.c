#include "test.h"

void test_hash_table() {
    check_start_group("hash_table_new()", 1);
    {
        hash_table *a = hash_table_new();

        check("!= NULL", a != NULL);
        check("->compare == NULL", a->compare == NULL);
        check("->hash == NULL", a->hash == NULL);
        check("->buckets == NULL", a->buckets == NULL);
        check("->buckets_count == 0", a->buckets_count == 0);
        check("->entries_count == 0", a->entries_count == 0);
    }
}
