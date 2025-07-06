#include "day05.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void day05_main(void) {
    char** input = file_to_array("./src/day05/data/input.txt");
    printf("2015:d05p1 - %u\n", day05_part1(input));
    printf("2015:d05p2 - %u\n", day05_part2(input));
    free_array((void**)input);
}

uint16_t day05_part1(char** input) {
    uint16_t nice       = 0;
    char*    invalids[] = {"ab", "cd", "pq", "xy", nullptr};

    for (char** i = input; *i; ++i) {
        for (char** n = invalids; *n; ++n) {
            if (strstr(*i, *n)) {
                goto outer;
            }
        }
        uint8_t vowels   = 0;
        bool    repeated = false;

        for (char* j = *i; *j != '\0'; ++j) {
            if (vowels < 3 && strchr("aeiou", *j)) {
                ++vowels;
            }
            if (!repeated && *(j + 1) != '\0' && *j == *(j + 1)) {
                repeated = true;
            }
            if ((int)repeated && vowels >= 3) {
                ++nice;
                break;
            }
        }
outer:
    }
    return nice;
}

uint16_t day05_part2(char**) {
    return 0;
}
