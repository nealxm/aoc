#include "day03.h"
#include "utils.h"

#include <assert.h>

int main(void) {
    assert(day03_part1(file_to_string("./data/example1.txt")) == 2);
    assert(day03_part1(file_to_string("./data/example2.txt")) == 4);
    assert(day03_part1(file_to_string("./data/example3.txt")) == 2);

    return 0;
}
