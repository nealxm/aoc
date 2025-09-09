#include "day23.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day23_tests[] = {
    TE("./data/example01.txt", "d23_p1_e01", one, 2),
    TE("./data/input.txt", "d23_p1_i", one, 170),
    TE("./data/input.txt", "d23_p2_i", two, 247),
    nullptr
};

int64_t day23_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day23_part1((const char* const*)input) : day23_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
