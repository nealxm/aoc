#include "day11.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const test_entry* day11_tests[] = {
    // TE("./data/input.txt", "d11_p1_i", one, ),
    // TE("./data/input.txt", "d11_p2_i", two, ),
    nullptr
};

// ideally u64 but testing framework needs all to be i64
int64_t day11_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int64_t r = (te->p == one) ? day11_part1(input) : day11_part2(input);
    free(input);
    return r;
}
