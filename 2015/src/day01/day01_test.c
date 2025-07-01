#include "day01.h"
#include "utils.h"

#include <assert.h>

int main(void) {
    assert(day01_part1(file_to_string("./data/example1.txt")) == 0);
    assert(day01_part1(file_to_string("./data/example2.txt")) == 0);
    assert(day01_part1(file_to_string("./data/example3.txt")) == 3);
    assert(day01_part1(file_to_string("./data/example4.txt")) == 3);
    assert(day01_part1(file_to_string("./data/example5.txt")) == 3);
    assert(day01_part1(file_to_string("./data/example6.txt")) == -1);
    assert(day01_part1(file_to_string("./data/example7.txt")) == -1);
    assert(day01_part1(file_to_string("./data/example8.txt")) == -3);
    assert(day01_part1(file_to_string("./data/example9.txt")) == -3);
    assert(day01_part1(file_to_string("./data/input.txt")) == 74);

    assert(day01_part2(file_to_string("./data/example10.txt")) == 1);
    assert(day01_part2(file_to_string("./data/example11.txt")) == 5);
    assert(day01_part2(file_to_string("./data/input.txt")) == 1795);

    return 0;
}
