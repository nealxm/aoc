#include "day08.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day08_tests[] = {
    TE("./data/example01.txt", "d08_p1_e01", one, 12),
    TE("./data/input.txt", "d08_p1_i", one, 1342),
    TE("./data/example01.txt", "d08_p2_e01", two, 19),
    TE("./data/input.txt", "d08_p2_i", two, 2074),
    nullptr
};

int64_t day08_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day08_part1((const char* const*)input) : day08_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
