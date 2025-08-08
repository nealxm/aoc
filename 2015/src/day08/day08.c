#include "day08.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day08_main(void) {
    char** input = file_to_array("./src/day08/data/input.txt");
    printf("2015:d08p1 - %hd\n", day08_part1(input));
    printf("2015:d08p2 - %hd\n", day08_part2(input));
    free_array((void**)input);
}

int16_t day08_part1(char** input) {
    uint16_t raw = 0, mem = 0;

    for (char** l = input; *l; ++l) {
        raw += strlen(*l);

        for (char* c = *l + 1; *(c + 1); ++c) {
            if (*c == '\\') {
                switch (*(c + 1)) {
                case '\\':
                case '\"':
                    ++mem;
                    ++c;
                    break;
                case 'x':
                    ++mem;
                    c += 3;
                    break;
                default:
                    fprintf(stderr, "invalid escape sequence: %c%c\n", *c, *(c + 1));
                    exit(1);
                }
            } else {
                ++mem;
            }
        }
    }
    return raw - mem;
}

int16_t day08_part2(char** input) {
    uint16_t raw = 0, enc = 0;

    for (char** l = input; *l; ++l) {
        raw += strlen(*l);
        enc += 2;

        for (char* c = *l; *c; ++c) {
            switch (*c) {
            case '\\':
            case '\"':
                enc += 2;
                break;
            default:
                ++enc;
            }
        }
    }
    return enc - raw;
}
