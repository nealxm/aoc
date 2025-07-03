#include "day02.h"
#include "testing.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const test_entry* day02_tests[] = {
    TE("./data/example01.txt", "d02_p1_e01", one, 58),
    TE("./data/example02.txt", "d02_p1_e02", one, 43),
    TE("./data/input.txt", "d02_p1_i", one, 1588178),
    TE("./data/example01.txt", "d02_p2_e01", two, 34),
    TE("./data/example02.txt", "d02_p2_e02", two, 14),
    TE("./data/input.txt", "d02_p2_i", two, 3783758),
};

int day02_test_run(const test_entry* te) {
    char** input = file_to_array(te->file);
    int    r     = (te->p == one) ? day02_part1(input) : day02_part2(input);
    free_array((void**)input);
    return r;
}
