#include "day25.h"
#include "testing_base.h"
#include "testing_registry.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>

const test_entry* day25_tests[] = {
    TE("./data/input.txt", "d25_p1_i", one, 9132360),
    nullptr
};

int64_t day25_test_run(const test_entry* te) {
    char* input = file_to_string(te->file);
    int64_t r = (te->p == one) ? day25_part1(input) : 0;
    free(input);
    return r;
}
