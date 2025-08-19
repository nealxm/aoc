#include "day07.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day07_tests[] = {
    TE("./data/example01.txt", "d07_p1_e01", one, 492),
    TE("./data/input.txt", "d07_p1_i", one, 46065),
    TE("./data/input.txt", "d07_p2_i", two, 14134),
    nullptr
};

int64_t day07_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day07_part1((const char* const*)input) : day07_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
