#include "day01.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day01_main(void) {
    char* input = file_to_string("./src/day01/data/input.txt");
    printf("2015:d01p1 - %hd\n", day01_part1(input));
    printf("2015:d01p2 - %hd\n", day01_part2(input));
    free(input);
}

int16_t day01_part1(const char* input) {
    int16_t floor = 0;
    for (const char* i = input; *i != '\0'; ++i) {
        if (*i == '(') {
            ++floor;
        } else if (*i == ')') {
            --floor;
        }
    }
    return floor;
}

int16_t day01_part2(const char* input) {
    int16_t floor = 0;
    for (int16_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '(') {
            ++floor;
        } else if (input[i] == ')') {
            --floor;
        }
        if (floor < 0) {
            return ++i;
        }
    }
    return -1;
}
