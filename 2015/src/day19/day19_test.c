#include "day19.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day19_tests[] = {
    TE("./data/example01.txt", "d19_p1_e01", one, 4),
    TE("./data/example02.txt", "d19_p1_e02", one, 7),
    TE("./data/input.txt", "d19_p1_i", one, 535),
    TE("./data/example01.txt", "d19_p2_e03", two, 3),
    TE("./data/example02.txt", "d19_p2_e04", two, 6),
    //TE("./data/input.txt", "d19_p2_i", two, ),
    nullptr
};

int64_t day19_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int64_t r = (te->p == one) ? day19_part1((const char* const*)input) : day19_part2((const char* const*)input);
    free_array((void**)input);
    return r;
}
