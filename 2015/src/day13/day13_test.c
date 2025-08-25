#include "day13.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day13_tests[] = {
    TE("./data/example01.txt", "d13_p1_e01", one, 330),
    TE("./data/input.txt", "d13_p1_i", one, 664),
    TE("./data/input.txt", "d13_p2_i", two, 640),
    nullptr
};

int64_t day13_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day13_part1((const char* const*)input) : day13_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
