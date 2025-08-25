#include "day09.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day09_tests[] = {
    TE("./data/example01.txt", "d09_p1_e01", one, 605),
    TE("./data/input.txt", "d09_p1_i", one, 141),
    TE("./data/example01.txt", "d09_p2_e01", two, 982),
    TE("./data/input.txt", "d09_p2_i", two, 736),
    nullptr
};

int64_t day09_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day09_part1((const char* const*)input) : day09_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
