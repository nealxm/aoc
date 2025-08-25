#include "day10.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const test_entry* day10_tests[] = {
    //no example tests without having function args
    TE("./data/input.txt", "d10_p1_i", one, 329356),
    TE("./data/input.txt", "d10_p2_i", two, 4666278),
    nullptr
};

//ideally u64 but testing framework needs all to be i64
int64_t day10_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    uint64_t r = (te->p == one) ? day10_part1(input) : day10_part2(input);
    free(input);

    if (r > INT64_MAX) {
        fprintf(stderr, "result too large: %llu\n", r);
        exit(1);
    }
    return (int64_t)r;
}
