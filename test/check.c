#include "check.h"

void check(char *message, int result) {
    result ? checks_passed++ : checks_failed++;
    check_print_indent(check_indent_level + 1);
    printf("\033[0;%dm%s\n", result ? 32 : 31, message);
}

void check_start_group(char *message, int indent_level) {
    check_print_indent(check_indent_level = indent_level);
    printf("\033[0;%dm%s\n", 34, message);
}

void check_print_indent(int level) {
    int i;
    for(i = 0; i < level * 4; i++) {
        printf(" ");
    }
}

void check_print_stats() {
    printf("\n\033[0;%dm%d checks, %d failures.\n",
            checks_failed ? 31 : 32,
            checks_passed + checks_failed,
            checks_failed);
}
