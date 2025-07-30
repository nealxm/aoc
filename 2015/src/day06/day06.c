#include "day06.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day06_main(void) {
    char** input = file_to_array("./src/day06/data/input.txt");
    printf("2015:d06p1 - %u\n", day06_part1(input));
    printf("2015:d06p2 - %u\n", day06_part2(input));
    free_array((void**)input);
}

typedef enum {
    off,
    on,
    toggle
} instr_kind;

typedef struct {
    uint16_t r, c;
} pos;

typedef struct {
    instr_kind kind;
    pos srt, end;
} instr;

typedef struct {
    bool grid[1000][1000];
    instr** instrs;
} state;

static void state_free(state* s) {
    free((void*)s->instrs);
    free(s);
}

static state* state_init(char** input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate memory for state\n");
        return nullptr;
    }
    for (uint16_t r = 0; r < 1000; ++r) {
        for (uint16_t c = 0; c < 1000; ++c) {
            s->grid[r][c] = false;
        }
    }
    uint8_t lines = 0;
    for (char** l = input; *l; ++l) {
        ++lines;
    }
    s->instrs = (instr**)malloc((lines + 1) * sizeof(*s->instrs));
    if (!s->instrs) {
        fprintf(stderr, "failed to allocate memory for instrs array\n");
        free(s);
        return nullptr;
    }
    for (uint8_t i = 0; i < lines; ++i) {
        char* l = input[i];
        instr_kind kind;
        uint16_t srt_r, srt_c, end_r, end_c;

        if (sscanf(l, "turn on %hu,%hu through %hu,%hu", &srt_c, &srt_r, &end_c, &end_r) == 4) {
            kind = on;
        } else if (sscanf(l, "turn off %hu,%hu through %hu,%hu", &srt_c, &srt_r, &end_c, &end_r) == 4) {
            kind = off;
        } else if (sscanf(l, "toggle %hu,%hu through %hu,%hu", &srt_c, &srt_r, &end_c, &end_r) == 4) {
            kind = toggle;
        } else {
            fprintf(stderr, "failed to parse instruction: %s\n", l);
            state_free(s);
            return nullptr;
        }
        s->instrs[i] = &(instr){.kind = kind, .srt = {.r = srt_r, .c = srt_c}, .end = {.r = end_r, .c = end_c}};
    }
    s->instrs[lines] = nullptr;
    return s;
}

uint32_t day06_part1(char** input) {
    state* s = state_init(input);
    return 0;
}

uint32_t day06_part2(char**) {
    return 0;
}
