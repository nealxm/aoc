#include "day06.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day06_tests[] = {
    TE("./data/example01.txt", "d06_p1_e01", one, 998996),
    TE("./data/input.txt", "d06_p1_i", one, 569999),
    TE("./data/example02.txt", "d06_p2_e02", two, 2000001),
    TE("./data/input.txt", "d06_p2_i", two, 17836115),
    nullptr
};

int64_t day06_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day06_part1(input) : day06_part2(input);
    free_array((void**)input);
    return r;
}
