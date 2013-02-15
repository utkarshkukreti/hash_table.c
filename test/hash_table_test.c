#include "test.h"

void test_hash_table() {
    check_start_group("hash_table_new()", 1);
    {
        hash_table *a = hash_table_new();

        check("!= NULL", a != NULL);
        check("->compare == NULL", a->compare == NULL);
        check("->hash == NULL", a->hash == NULL);
        check("->buckets != NULL", a->buckets != NULL);
        check("->buckets_count > 0", a->buckets_count > 0);
        check("->entries_count == 0", a->entries_count == 0);
    }

    check_start_group("hash_table_{get,put}", 1);
    {
        hash_table *a = hash_table_new();
        a->compare = hash_table_int_compare;
        a->hash = hash_table_int_hash;
        // key and value can only be pointers
        int i1 = 10, i2 = 20, i3 = 30;
        check("entries_count == 0", a->entries_count == 0);
        check("put i1, i2", hash_table_put(a, &i1, &i2));
        check("entries_count == 1", a->entries_count == 1);
        check("get i1 == i2", hash_table_get(a, &i1) == &i2);
        check("get i2 == NULL", hash_table_get(a, &i2) == NULL);
        check("put i1, i3", hash_table_put(a, &i1, &i3));
        check("entries_count == 1", a->entries_count == 1);
        check("get i1 == i3", hash_table_get(a, &i1) == &i3);
    }
}
