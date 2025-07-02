#include "day03.h"
#include "utils.h"

#include <assert.h>

int main(void) {
    assert(day03_part1(file_to_string("./data/example1.txt")) == 2);
    assert(day03_part1(file_to_string("./data/example2.txt")) == 4);
    assert(day03_part1(file_to_string("./data/example3.txt")) == 2);
    assert(day03_part1(file_to_string("./data/input.txt")) == 2081);

    assert(day03_part2(file_to_string("./data/example4.txt")) == 3);
    assert(day03_part2(file_to_string("./data/example2.txt")) == 3);
    assert(day03_part2(file_to_string("./data/example3.txt")) == 11);
    assert(day03_part2(file_to_string("./data/input.txt")) == 2341);
    return 0;
}
