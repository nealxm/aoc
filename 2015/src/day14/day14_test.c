#include "day14.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day14_tests[] = {
    //no example tests without having function args
    TE("./data/input.txt", "d14_p1_i", one, 2655),
    TE("./data/input.txt", "d14_p2_i", two, 1059),
    nullptr
};

int64_t day14_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day14_part1((const char* const*)input) : day14_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
