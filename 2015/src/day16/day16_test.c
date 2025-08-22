#include "day16.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day16_tests[] = {
    TE("./data/input.txt", "d16_p1_i", one, 103),
    TE("./data/input.txt", "d16_p2_i", two, 405),
    nullptr
};

int64_t day16_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day16_part1((const char* const*)input) : day16_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
