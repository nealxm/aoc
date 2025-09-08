#include "day11.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>

static int64_t str_to_b26(const char* str) {
    int64_t res = 0;
    for (const char* c = str; *c; ++c) {
        res = (res * 26) + (*c - 'a');
    }
    return res;
}

const test_entry* day11_tests[] = {
    TE("./data/example01.txt", "d11_p1_e01", one, 334140716LL),
    TE("./data/example02.txt", "d11_p1_e02", one, 50460204602LL),
    TE("./data/input.txt", "d11_p1_i", one, 21124136747LL),
    TE("./data/input.txt", "d11_p2_i", two, 21125087258LL),
    nullptr
};

int64_t day11_test_run(const test_entry* te) {
    //assert(str_to_b26("abcdffaa") == day11_tests[0]->expected);
    //assert(str_to_b26("ghjaabcc") == day11_tests[1]->expected);
    //assert(str_to_b26("cqjxxyzz") == day11_tests[2]->expected);
    //assert(str_to_b26("cqkaabcc") == day11_tests[3]->expected);

    char* input = file_to_string(te->file);
    char* r = (te->p == one) ? day11_part1(input) : day11_part2(input);
    int64_t res = str_to_b26(r);
    free(input);
    free(r);
    return res;
}
