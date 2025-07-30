#include "day06.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day06_tests[] = {
    TE("./data/example01.txt", "d06_p1_e01", one, 998996),
    // TE("./data/input.txt", "d06_p1_i", one, ),
    nullptr
};

int64_t day06_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day06_part1(input) : day06_part2(input);
    free_array((void**)input);
    return r;
}
