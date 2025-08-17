#include "day14.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day14_tests[] = {
    TE("./data/input.txt", "d14_p1_i", one, 2655),
    // TE("./data/input.txt", "d14_p2_i", two, ),
    nullptr
};

int64_t day14_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day14_part1(input) : day14_part2(input);
    free_array((void**)input);
    return r;
}
