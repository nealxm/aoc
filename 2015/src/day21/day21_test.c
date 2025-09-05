#include "day21.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day21_tests[] = {
    TE("./data/input.txt", "d21_p1_i", one, 121),
    TE("./data/input.txt", "d21_p2_i", two, 201),
    nullptr
};

int64_t day21_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day21_part1((const char* const*)input) : day21_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
