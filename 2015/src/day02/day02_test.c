#include "day02.h"
#include "utils.h"

#include <assert.h>

int main(void) {
    assert(day02_part1(file_to_array("./data/example1.txt")) == 58);
    assert(day02_part1(file_to_array("./data/example2.txt")) == 43);
    assert(day02_part1(file_to_array("./data/input.txt")) == 1588178);

    return 0;
}
