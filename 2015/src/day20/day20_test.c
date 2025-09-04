#include "day20.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const test_entry* day20_tests[] = {
    TE("./data/input.txt", "d20_p1_i", one, 831600),
    TE("./data/input.txt", "d20_p2_i", two, 884520),
    nullptr
};

int64_t day20_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int64_t r = (te->p == one) ? day20_part1(input) : day20_part2(input);
    free(input);
    return r;
}
