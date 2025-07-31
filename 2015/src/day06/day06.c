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
    uint8_t b_grid[1000][1000];
    instr** instrs;
} state;

static void state_free(state* s) {
    for (instr** p = s->instrs; *p; ++p) {
        free(*p);
    }
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
    uint16_t lines = 0;
    for (char** l = input; *l; ++l) {
        ++lines;
    }
    s->instrs = (instr**)malloc((lines + 1) * sizeof(instr*));
    if (!s->instrs) {
        fprintf(stderr, "failed to allocate memory for instrs array\n");
        free(s);
        return nullptr;
    }
    for (uint16_t i = 0; i < lines; ++i) {
        char* l = input[i];
        instr_kind kind;
        uint16_t srt_r, srt_c, end_r, end_c;

        if (sscanf(l, "turn off %hu,%hu through %hu,%hu", &srt_c, &srt_r, &end_c, &end_r) == 4) {
            kind = off;
        } else if (sscanf(l, "turn on %hu,%hu through %hu,%hu", &srt_c, &srt_r, &end_c, &end_r) == 4) {
            kind = on;
        } else if (sscanf(l, "toggle %hu,%hu through %hu,%hu", &srt_c, &srt_r, &end_c, &end_r) == 4) {
            kind = toggle;
        } else {
            fprintf(stderr, "failed to parse instruction: %s\n", l);
            state_free(s);
            return nullptr;
        }
        instr* new_instr = malloc(sizeof(instr));
        *new_instr = (instr){.kind = kind, .srt = {.r = srt_r, .c = srt_c}, .end = {.r = end_r, .c = end_c}};
        s->instrs[i] = new_instr;
    }
    s->instrs[lines] = nullptr;
    return s;
}

uint32_t day06_part1(char** input) {
    state* s = state_init(input);
    for (instr** i = s->instrs; *i; ++i) {
        instr* curr = *i;

        for (uint16_t r = curr->srt.r; r <= curr->end.r; ++r) {
            for (uint16_t c = curr->srt.c; c <= curr->end.c; ++c) {
                switch (curr->kind) {
                case off:
                    s->grid[r][c] = false;
                    break;
                case on:
                    s->grid[r][c] = true;
                    break;
                case toggle:
                    s->grid[r][c] = !s->grid[r][c];
                    break;
                default:
                    fprintf(stderr, "invalid instruction kind: %u\n", curr->kind);
                    break;
                }
            }
        }
    }
    uint32_t total = 0;
    for (uint16_t r = 0; r < 1000; ++r) {
        for (uint16_t c = 0; c < 1000; ++c) {
            total += s->grid[r][c];
        }
    }
    state_free(s);
    return total;
}

uint32_t day06_part2(char** input) {
    state* s = state_init(input);
    for (instr** i = s->instrs; *i; ++i) {
        instr* curr = *i;

        for (uint16_t r = curr->srt.r; r <= curr->end.r; ++r) {
            for (uint16_t c = curr->srt.c; c <= curr->end.c; ++c) {
                switch (curr->kind) {
                case off:
                    if (s->b_grid[r][c] > 0) {
                        s->b_grid[r][c] -= 1;
                    }
                    break;
                case on:
                    s->b_grid[r][c] += 1;
                    break;
                case toggle:
                    s->b_grid[r][c] += 2;
                    break;
                default:
                    fprintf(stderr, "invalid instruction kind: %u\n", curr->kind);
                    break;
                }
            }
        }
    }
    uint32_t total = 0;
    for (uint16_t r = 0; r < 1000; ++r) {
        for (uint16_t c = 0; c < 1000; ++c) {
            total += s->b_grid[r][c];
        }
    }
    state_free(s);
    return total;
}
