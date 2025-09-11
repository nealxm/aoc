#include "day24.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day24_tests[] = {
    TE("./data/example01.txt", "d24_p1_e01", one, 99),
    TE("./data/input.txt", "d24_p1_i", one, 10723906903),
    TE("./data/input.txt", "d24_p2_i", two, 74850409),
    nullptr
};

int64_t day24_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day24_part1((const char* const*)input) : day24_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
