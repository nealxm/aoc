#include "day01.h"

#include "utils.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day01_main(void) {
    char* input = file_to_string("./src/day01/data/input.txt");
    printf("2015:d01p1 - %d\n", day01_part1(input));
    printf("2015:d01p2 - %d\n", day01_part2(input));
    free(input);
}

int day01_part1(const char* input) {
    int floor = 0;
    for (const char* i = input; *i != '\0'; i++) {
        if (*i == '(') {
            floor++;
        } else if (*i == ')') {
            floor--;
        }
    }
    return floor;
}

int day01_part2(const char* input) {
    int floor = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(') {
            floor++;
        } else if (input[i] == ')') {
            floor--;
        }
        if (floor < 0) {
            return i + 1;
        }
    }
    return -1;
}
