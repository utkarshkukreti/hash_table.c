#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>

int checks_passed, checks_failed, check_indent_level;

void check(char *message, int result);
void check_start_group(char *message, int indent_level);
void check_print_indent();
void check_print_stats();

#endif
