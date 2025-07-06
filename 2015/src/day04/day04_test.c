#include "day04.h"
#include "testing.h"
#include "utils.h"

#include <stdlib.h>

const test_entry* day04_tests[] = {
    TE("./data/example01.txt", "d04_p1_e01", one, 609043),
    TE("./data/example02.txt", "d04_p1_e02", one, 1048970),
    TE("./data/input.txt", "d04_p1_i", one, 346386),
    TE("./data/input.txt", "d04_p2_i", two, 9958218),
    nullptr
};

int day04_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int   r     = (te->p == one) ? day04_part1(input) : day04_part2(input);
    free(input);
    return r;
}
