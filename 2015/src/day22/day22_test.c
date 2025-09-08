#include "day22.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day22_tests[] = {
    TE("./data/input.txt", "d22_p1_i", one, 900),
    TE("./data/input.txt", "d22_p2_i", two, 1216),
    nullptr
};

int64_t day22_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day22_part1((const char* const*)input) : day22_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
