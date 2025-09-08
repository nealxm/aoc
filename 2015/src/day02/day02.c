#include "day02.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day02_main(void) {
    char** input = file_to_array("./src/day02/data/input.txt");
    printf("2015:d02p1 - %u\n", day02_part1((const char* const*)input));
    printf("2015:d02p2 - %u\n", day02_part2((const char* const*)input));
    free_array((void**)input);
}

uint32_t day02_part1(const char* const* input) {
    uint32_t total = 0;
    for (const char* const* i = input; *i != nullptr; i++) {
        uint8_t l, w, h;
        if (sscanf(*i, "%hhux%hhux%hhu", &l, &w, &h) != 3) {
            fprintf(stderr, "failed to parse line '%s'\n", *i);
            exit(1);
        }
        uint16_t s1 = l * w;
        uint16_t s2 = w * h;
        uint16_t s3 = h * l;
        total += (2 * (s1 + s2 + s3)) + (uint32_t)min(3, s1, s2, s3);
    }
    return total;
}

uint32_t day02_part2(const char* const* input) {
    uint32_t total = 0;
    for (const char* const* i = input; *i != nullptr; i++) {
        uint8_t l, w, h;
        if (sscanf(*i, "%hhux%hhux%hhu", &l, &w, &h) != 3) {
            fprintf(stderr, "failed to parse line '%s'\n", *i);
            exit(1);
        }
        total += (2 * (l + w + h - (uint32_t)max(3, l, w, h))) + (l * w * h);
    }
    return total;
}
