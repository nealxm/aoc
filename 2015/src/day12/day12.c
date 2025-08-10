#include "day12.h"

#include "utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day12_main(void) {
    char* input = file_to_string("./src/day12/data/input.txt");
    printf("2015:d12p1 - %d\n", day12_part1(input));
    printf("2015:d12p2 - %d\n", day12_part2(input));
    free(input);
}

int32_t day12_part1(const char* input) {
    int32_t sum = 0;
    const char* csr = input;

    while (*csr) {
        if (*csr == '-' || (*csr >= '0' && *csr <= '9')) {
            char* end;
            sum += strtol(csr, &end, 10);
            csr = end;
        } else {
            ++csr;
        }
    }
    return sum;
}

typedef struct {
    int32_t sum;
    bool red;
    uint8_t start_ad;
} obj_state;

int32_t day12_part2(const char* input) {
    int32_t sum = 0;
    uint8_t cap = 1, obj_depth = 0, arr_depth = 0;
    const char* csr = input;

    obj_state* obj_stack = malloc(cap * sizeof(obj_state));
    if (!obj_stack) {
        fprintf(stderr, "failed to allocate obj_stack");
        exit(1);
    }
    while (*csr) {
        if (*csr == '{') {
            ++obj_depth;

            if (obj_depth > cap) {
                obj_state* new = realloc(obj_stack, (++cap) + sizeof(obj_state));
                if (!new) {
                    free(obj_stack);
                    fprintf(stderr, "failed to reallocate obj_stack");
                    exit(1);
                }
                obj_stack = new;
            }
            obj_stack[obj_depth - 1] = (obj_state){0, false, arr_depth};
        } else if (*csr == '}') {
            assert(obj_depth >= 1);

            if (!obj_stack[obj_depth - 1].red) {
                if (obj_depth == 1) {
                    sum += obj_stack[obj_depth - 1].sum;
                } else {
                    obj_stack[obj_depth - 2].sum += obj_stack[obj_depth - 1].sum;
                }
            }
            --obj_depth;
        } else if (*csr == '[') {
            ++arr_depth;
        } else if (*csr == ']') {
            assert(arr_depth >= 1);

            --arr_depth;
        } else if (obj_depth >= 1 && !obj_stack[obj_depth - 1].red && obj_stack[obj_depth - 1].start_ad == arr_depth &&
                   *csr == 'r' && csr[1] == 'e' && csr[2] == 'd') {
            obj_stack[obj_depth - 1].red = true;
            csr += 3;
            continue;
        } else if (*csr == '-' || (*csr >= '0' && *csr <= '9')) {
            char* end;
            int64_t num = strtol(csr, &end, 10);

            if (obj_depth >= 1) {
                obj_stack[obj_depth - 1].sum += num;
            } else {
                sum += num;
            }
            csr = end;
            continue;
        }
        ++csr;
    }
    free(obj_stack);
    return sum;
}
