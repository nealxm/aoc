#include "day20.h"

#include "utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day20_main(void) {
    char* input = file_to_string("./src/day20/data/input.txt");
    printf("2015:d20p1 - %u\n", day20_part1(input));
    printf("2015:d20p2 - %u\n", day20_part2(input));
    free(input);
}

typedef struct {
    uint32_t tgt, h_cmax, h_pmax;
    uint32_t* presents;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    free(s->presents);
    free(s);
}

static state* state_init(const char* input) {
    state* s = malloc(sizeof(state));
    uint64_t val = (uint64_t)atoi(input);
    assert(val < UINT32_MAX);
    s->tgt = (uint32_t)val;

    s->h_cmax = 1;
    s->h_pmax = 1;
    s->presents = calloc(s->h_cmax, sizeof(uint32_t));
    return s;
}

uint32_t day20_part1(const char* input) {
    state* s = state_init(input);
    s->presents[0] = 10;
    uint32_t out = 0;

    while (true) {
        for (uint32_t h = s->h_pmax; h <= s->h_cmax; ++h) {
            if (s->presents[h - 1] >= s->tgt) {
                out = h;
                goto end;
            }
        }
        s->h_pmax = s->h_cmax;
        s->h_cmax *= 2;
        uint32_t* new = realloc(s->presents, s->h_cmax * sizeof(uint32_t));
        if (!new) {
            fprintf(stderr, "failed to reallocate presents");
            goto end;
        }
        s->presents = new;

        for (uint32_t e = s->h_pmax + 1; e <= s->h_cmax; ++e) {
            for (uint32_t h = e; h <= s->h_cmax; h += e) {
                if (h % e != 0) {
                    continue;
                }
                s->presents[h - 1] += e * 10;
            }
        }
        for (uint32_t e = 1; e <= s->h_pmax; ++e) {
            uint32_t h_srt = ((s->h_pmax / e) + 1) * e;

            for (uint32_t h = h_srt; h <= s->h_cmax; h += e) {
                if (h % e != 0) {
                    continue;
                }
                s->presents[h - 1] += e * 10;
            }
        }
    }
end:
    state_free(s);
    return out;
}

uint32_t day20_part2(const char* input) {
    state* s = state_init(input);
    s->presents[0] = 11;
    uint32_t out = 0;

    while (true) {
        for (uint32_t h = s->h_pmax; h <= s->h_cmax; ++h) {
            if (s->presents[h - 1] >= s->tgt) {
                out = h;
                goto end;
            }
        }
        s->h_pmax = s->h_cmax;
        s->h_cmax *= 2;
        uint32_t* new = realloc(s->presents, s->h_cmax * sizeof(uint32_t));
        if (!new) {
            fprintf(stderr, "failed to reallocate presents");
            goto end;
        }
        s->presents = new;

        for (uint32_t e = s->h_pmax + 1; e <= s->h_cmax; ++e) {
            for (uint32_t h = e; h <= s->h_cmax; h += e) {
                if (h % e != 0 || h > e * 50) {
                    continue;
                }
                s->presents[h - 1] += e * 11;
            }
        }
        for (uint32_t e = 1; e <= s->h_pmax; ++e) {
            uint32_t h_srt = ((s->h_pmax / e) + 1) * e;

            for (uint32_t h = h_srt; h <= s->h_cmax; h += e) {
                if (h % e != 0 || h > e * 50) {
                    continue;
                }
                s->presents[h - 1] += e * 11;
            }
        }
    }
end:
    state_free(s);
    return out;
}
