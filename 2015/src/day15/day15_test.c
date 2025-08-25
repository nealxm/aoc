#include "day15.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day15_tests[] = {
    TE("./data/example01.txt", "d15_p1_e01", one, 62842880),
    TE("./data/input.txt", "d15_p1_i", one, 18965440),
    TE("./data/example01.txt", "d15_p2_e01", two, 57600000),
    TE("./data/input.txt", "d15_p2_i", two, 15862900),
    nullptr
};

int64_t day15_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day15_part1((const char* const*)input) : day15_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
