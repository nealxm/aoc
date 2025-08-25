#include "day18.h"

#include "utils.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day18_main(void) {
    char** input = file_to_array("./src/day18/data/input.txt");
    printf("2015:d18p1 - %hu\n", day18_part1((const char* const*)input));
    printf("2015:d18p2 - %hu\n", day18_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    bool on;
    uint8_t neig;
} cell;

typedef struct {
    cell*** grid;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (cell*** r = s->grid; *r; ++r) {
        for (cell** c = *r; *c; ++c) {
            free(*c);
        }
        free((void*)*r);
    }
    free((void*)s->grid);
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    s->grid = (cell***)calloc(100 + 1, sizeof(cell**));
    if (!s || !s->grid) {
        fprintf(stderr, "failed to allocate memory for state or grid\n");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        ptrdiff_t i = l - input;
        s->grid[i] = (cell**)calloc(100 + 1, sizeof(cell*));
        if (!s->grid[i]) {
            fprintf(stderr, "failed to allocate memory for row\n");
            goto bad_exit;
        }

        for (const char* c = *l; *c; ++c) {
            ptrdiff_t j = c - *l;

            bool on;
            switch (*c) {
            case '.':
                on = false;
                break;
            case '#':
                on = true;
                break;
            default:
                fprintf(stderr, "failed to parse character\n");
                goto bad_exit;
            }
            s->grid[i][j] = malloc(sizeof(cell));
            if (!s->grid[i][j]) {
                fprintf(stderr, "failed to allocate memory for cell");
                goto bad_exit;
            }

            *(s->grid[i][j]) = (cell){
                .on = on,
                .neig = 0
            };
        }
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

static uint16_t game_of_life(state* s, bool sticky) {
    if (sticky) {
        s->grid[0][0]->on = true;
        s->grid[0][99]->on = true;
        s->grid[99][99]->on = true;
        s->grid[99][0]->on = true;
    }

    for (uint8_t k = 1; k <= 100; ++k) {

        for (cell*** r = s->grid; *r; ++r) {
            uint8_t i = (uint8_t)(r - s->grid);

            for (cell** c = *r; *c; ++c) {
                uint8_t j = (uint8_t)(c - *r);
                (*c)->neig = 0;

                if (
                    sticky &&
                    ((i == 0 && j == 0) || (i == 0 && j == 99) || (i == 99 && j == 99) || (i == 99 && j == 0))
                ) {
                    continue;
                }
                for (int n_r = i - 1; n_r <= i + 1; ++n_r) {
                    for (int n_c = j - 1; n_c <= j + 1; ++n_c) {
                        if (
                            !(n_r >= 0 && n_r < 100 && n_c >= 0 && n_c < 100) ||
                            (n_r == i && n_c == j)
                        ) {
                            continue;
                        }
                        if (s->grid[n_r][n_c]->on) {
                            ++((*c)->neig);
                        }
                    }
                }
            }
        }
        for (cell*** r = s->grid; *r; ++r) {
            uint8_t i = (uint8_t)(r - s->grid);

            for (cell** c = *r; *c; ++c) {
                uint8_t j = (uint8_t)(c - *r);

                if (
                    sticky &&
                    ((i == 0 && j == 0) || (i == 0 && j == 99) || (i == 99 && j == 99) || (i == 99 && j == 0))
                ) {
                    continue;
                }
                if ((*c)->on) {
                    if ((*c)->neig == 2 || (*c)->neig == 3) {
                        continue;
                    }
                    (*c)->on = false;
                } else {
                    if ((*c)->neig == 3) {
                        (*c)->on = true;
                    }
                }
            }
        }
    }
    uint16_t out = 0;
    for (cell*** r = s->grid; *r; ++r) {
        for (cell** c = *r; *c; ++c) {
            if ((*c)->on) {
                ++out;
            }
        }
    }
    return out;
}

uint16_t day18_part1(const char* const* input) {
    state* s = state_init(input);
    uint16_t out = game_of_life(s, false);
    state_free(s);
    return out;
}

uint16_t day18_part2(const char* const* input) {
    state* s = state_init(input);
    uint16_t out = game_of_life(s, true);
    state_free(s);
    return out;
}
