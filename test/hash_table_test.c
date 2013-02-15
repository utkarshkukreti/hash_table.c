#include "test.h"

// http://xkcd.com/221/
static unsigned int get_random_number(void *a);

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

    check_start_group("hash_table_{get,put} with bad hashing function", 1);
    {
        hash_table *a = hash_table_new();
        a->compare = hash_table_int_compare;
        a->hash = get_random_number;
        // key and value can only be pointers
        int i1 = 10, i2 = 20, i3 = 30;
        check("entries_count == 0", a->entries_count == 0);
        check("put i1, i2", hash_table_put(a, &i1, &i2));
        check("entries_count == 1", a->entries_count == 1);
        check("put i2, i3", hash_table_put(a, &i2, &i3));
        check("entries_count == 2", a->entries_count == 2);
        check("get i2 == i3", hash_table_get(a, &i2) == &i3);
        check("put i3, i1", hash_table_put(a, &i3, &i1));
        check("entries_count == 3", a->entries_count == 3);
        check("get i3 == i1", hash_table_get(a, &i3) == &i1);
        check("buckets[4]->next != NULL", a->buckets[4]->next != NULL);
        check("buckets[4]->next->next != NULL",
                a->buckets[4]->next->next != NULL);
    }

    check_start_group("multiple hash_table_{get,put} should resize buckets", 1);
    {
        hash_table *a = hash_table_new();
        a->compare = hash_table_int_compare;
        a->hash = hash_table_int_hash;
        int i;
        int *array = malloc(sizeof(int) * 100);
        for(i = 0; i < 100; i++) {
            array[i] = i;
            hash_table_put(a, &array[i], &array[i]);
        }
        check("entries_count == 100", a->entries_count == 100);
        check("buckets_count > 5", a->buckets_count > 5);
        check("get 15 == 15", hash_table_get(a, &array[15]) == &array[15]);
        check("get 66 == 66", hash_table_get(a, &array[66]) == &array[66]);
        check("get 97 == 97", hash_table_get(a, &array[97]) == &array[97]);
    }

    check_start_group("hash_table_delete()", 1);
    {
        hash_table *a = hash_table_new();
        a->compare = hash_table_int_compare;
        a->hash = hash_table_int_hash;
        int i1 = 1, i2 = 2;
        check("entries_count == 0", a->entries_count == 0);
        check("delete i1 == false", hash_table_delete(a, &i1) == false);
        check("put i1, i2", hash_table_put(a, &i1, &i2) == true);
        check("entries_count == 1", a->entries_count == 1);
        check("delete i1", hash_table_delete(a, &i1) == true);
        check("entries_count == 0", a->entries_count == 0);
        check("get i1 == NULL", hash_table_get(a, &i1) == NULL);
        check("delete i1", hash_table_delete(a, &i1) == false);
        check("entries_count == 0", a->entries_count == 0);
    }
}

// http://xkcd.com/221/
static unsigned int get_random_number(void *a) {
    return 4; // chosen by fair dice roll.
              // guaranteed to be random.
}
