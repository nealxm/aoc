#include "day03.h"
#include "testing.h"
#include "utils.h"

#include <stdlib.h>

const test_entry* day03_tests[] = {
    TE("./data/example01.txt", "d03_p1_e01", one, 2),
    TE("./data/example02.txt", "d03_p1_e02", one, 4),
    TE("./data/example03.txt", "d03_p1_e03", one, 2),
    TE("./data/input.txt", "d03_p1_i", one, 2081),
    TE("./data/example04.txt", "d03_p2_e04", two, 3),
    TE("./data/example02.txt", "d03_p2_e02", two, 3),
    TE("./data/example03.txt", "d03_p2_e03", two, 11),
    TE("./data/input.txt", "d03_p2_i", two, 2341),
    nullptr
};

int day03_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int   r     = (te->p == one) ? day03_part1(input) : day03_part2(input);
    free(input);
    return r;
}
