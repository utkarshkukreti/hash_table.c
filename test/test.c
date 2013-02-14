#include "test.h"

int main() {
    test_hash_table();
    check_print_stats();

    return checks_failed;
}
