#include "day18.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day18_tests[] = {
    //no example tests without having function args
    TE("./data/input.txt", "d18_p1_i", one, 814),
    TE("./data/input.txt", "d18_p2_i", two, 924),
    nullptr
};

int64_t day18_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day18_part1((const char* const*)input) : day18_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
