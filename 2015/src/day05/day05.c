#include "day05.h"

#include "utils.h"

#include <stddef.h>
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
    uint16_t nice = 0;
    char* invalids[] = {"ab", "cd", "pq", "xy", nullptr};

    for (char** i = input; *i; ++i) {
        for (char** n = invalids; *n; ++n) {
            if (strstr(*i, *n)) {
                goto outer;
            }
        }
        uint8_t vowels = 0;
        bool repeated = false;

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

uint16_t day05_part2(char** input) {
    uint16_t nice = 0;
    for (char** i = input; *i; ++i) {
        bool cond1 = false, cond2 = false;

        for (char* j = *i; *(j + 2) != '\0'; ++j) {
            if (*j == *(j + 2)) {
                cond2 = true;
                break;
            }
        }
        int8_t pair_pos[26][26];
        memset(pair_pos, -1, sizeof(pair_pos));

        for (char* j = *i; *(j + 1) != '\0'; ++j) {
            int8_t fst = *j - 'a';
            int8_t snd = *(j + 1) - 'a';
            ptrdiff_t curr = j - *i;

            if (pair_pos[fst][snd] == -1) {
                pair_pos[fst][snd] = (int8_t)curr;
            } else {
                if (curr - pair_pos[fst][snd] >= 2) {
                    cond1 = true;
                    break;
                }
            }
        }
        if (cond1 && cond2) {
            ++nice;
        }
    }
    return nice;
}
