#include "day11.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day11_main(void) {
    char* input = file_to_string("./src/day11/data/input.txt");
    printf("2015:d11p1 - %hu\n", day11_part1(input));
    printf("2015:d11p2 - %hu\n", day11_part2(input));
    free(input);
}

uint16_t day11_part1(const char*) {
    return 0;
}

uint16_t day11_part2(const char*) {
    return 0;
}
