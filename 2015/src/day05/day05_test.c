#include "day05.h"
#include "testing.h"
#include "utils.h"

#include <stdint.h>

const test_entry* day05_tests[] = {
    TE("./data/example01.txt", "d05_p1_e01", one, 1),
    TE("./data/example02.txt", "d05_p1_e02", one, 0),
    TE("./data/example03.txt", "d05_p1_e03", one, 0),
    TE("./data/example04.txt", "d05_p1_e04", one, 0),
    TE("./data/input.txt", "d05_p1_i", one, 258)
};

int64_t day05_test_run(const test_entry* te) {
    char**  input = file_to_array(te->file);
    int64_t r     = (te->p == one) ? day05_part1(input) : day05_part2(input);
    free_array((void**)input);
    return r;
}
