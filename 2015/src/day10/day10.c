#include "day10.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day10_main(void) {
    char* input = file_to_string("./src/day10/data/input.txt");
    printf("2015:d10p1 - %u\n", day10_part1(input));
    printf("2015:d10p2 - %llu\n", day10_part2(input));
    free(input);
}

static char* look_and_say(const char* input) {
    char* out = malloc((strlen(input) * 2) + 1);
    char* csr = out;

    while (*input) {
        char dig = *input;
        uint8_t cnt = 1;

        while (input[cnt] && input[cnt] == dig) {
            ++cnt;
        }
        csr += sprintf(csr, "%hhu%c", cnt, dig);
        input += cnt;
    }
    *csr = '\0';
    return out;
}

uint32_t day10_part1(const char* input) {
    char* curr = strdup(input);

    for (uint8_t i = 0; i < 40; ++i) {
        char* next = look_and_say(curr);
        free(curr);
        curr = next;
    }
    uint32_t len = (uint32_t)strlen(curr);
    free(curr);
    return len;
}

uint64_t day10_part2(const char* input) {
    char* curr = strdup(input);

    for (uint8_t i = 0; i < 50; ++i) {
        char* next = look_and_say(curr);
        free(curr);
        curr = next;
    }
    uint32_t len = (uint32_t)strlen(curr);
    free(curr);
    return len;
}
