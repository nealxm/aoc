#include "day01.h"
#include "testing.h"
#include "utils.h"

#include <stdlib.h>

const test_entry* day01_tests[] = {
    TE("./data/example01.txt", "d01_p1_e01", one, 0),
    TE("./data/example02.txt", "d01_p1_e02", one, 0),
    TE("./data/example03.txt", "d01_p1_e03", one, 3),
    TE("./data/example04.txt", "d01_p1_e04", one, 3),
    TE("./data/example05.txt", "d01_p1_e05", one, 3),
    TE("./data/example06.txt", "d01_p1_e06", one, -1),
    TE("./data/example07.txt", "d01_p1_e07", one, -1),
    TE("./data/example08.txt", "d01_p1_e08", one, -3),
    TE("./data/example09.txt", "d01_p1_e09", one, -3),
    TE("./data/input.txt", "d01_p1_i", one, 74),
    TE("./data/example10.txt", "d01_p2_e10", two, 1),
    TE("./data/example11.txt", "d01_p2_e11", two, 5),
    TE("./data/input.txt", "d01_p2_i", two, 1795),
    nullptr
};

int day01_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int   r     = (te->p == one) ? day01_part1(input) : day01_part2(input);
    free(input);
    return r;
}
