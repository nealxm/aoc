#include "day12.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>

const test_entry* day12_tests[] = {
    TE("./data/example01.txt", "d12_p1_e01", one, 6),
    TE("./data/example02.txt", "d12_p1_e02", one, 6),
    TE("./data/example03.txt", "d12_p1_e03", one, 3),
    TE("./data/example04.txt", "d12_p1_e04", one, 3),
    TE("./data/example05.txt", "d12_p1_e05", one, 0),
    TE("./data/example06.txt", "d12_p1_e06", one, 0),
    TE("./data/example07.txt", "d12_p1_e07", one, 0),
    TE("./data/example08.txt", "d12_p1_e08", one, 0),
    TE("./data/input.txt", "d12_p1_i", one, 156366),
    TE("./data/example01.txt", "d12_p2_e01", two, 6),
    TE("./data/example09.txt", "d12_p2_e09", two, 4),
    TE("./data/example10.txt", "d12_p2_e10", two, 0),
    TE("./data/example11.txt", "d12_p2_e11", two, 6),
    TE("./data/input.txt", "d12_p2_i", two, 96852),
    nullptr
};

int64_t day12_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int64_t r = (te->p == one) ? day12_part1(input) : day12_part2(input);
    free(input);
    return r;
}
