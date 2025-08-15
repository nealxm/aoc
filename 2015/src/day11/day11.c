#include "day11.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day11_main(void) {
    char* input = file_to_string("./src/day11/data/input.txt");
    char* curr = day11_part1(input);

    printf("2015:d11p1 - %s\n", curr);
    free(curr);
    curr = day11_part2(curr);
    printf("2015:d11p2 - %s\n", curr);

    free(curr);
    free(input);
}

static bool paswd_valid(const char* pass) {
    const char* invalids = "iol";
    bool cons = false;
    uint8_t pair = 0;

    for (const char* c = pass; *c != '\0'; ++c) {
        for (const char* i = invalids; *i != '\0'; ++i) {
            if (*c == *i) {
                return false;
            }
        }
        if (!cons && c[1] != '\0' && c[2] != '\0' && c[1] == c[0] + 1 && c[2] == c[1] + 1) {
            cons = true;
        }
        if (pair < 2 && c[1] != '\0' && c[0] == c[1] && (c == pass || c[0] != c[-1])) {
            ++pair;
        }
    }
    return cons && pair >= 2;
}

static void paswd_inc(char* pass, uint8_t pos) {
    if (pass[pos] != 'z') {
        ++pass[pos];
    } else {
        pass[pos] = 'a';
        paswd_inc(pass, pos - 1);
    }
}

char* day11_part1(const char* input) {
    char* curr = strdup(input);
    do {
        paswd_inc(curr, 7);
    } while (!paswd_valid(curr));
    return curr;
}

char* day11_part2(const char* input) {
    char* curr = day11_part1(input);
    do {
        paswd_inc(curr, 7);
    } while (!paswd_valid(curr));
    return curr;
}
