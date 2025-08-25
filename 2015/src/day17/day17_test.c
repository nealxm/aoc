#include "day17.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day17_tests[] = {
    //no example tests without having function args
    TE("./data/input.txt", "d17_p1_i", one, 4372),
    TE("./data/input.txt", "d17_p2_i", two, 4),
    nullptr
};

int64_t day17_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day17_part1((const char* const*)input) : day17_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
