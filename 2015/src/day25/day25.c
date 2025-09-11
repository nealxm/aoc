#include "day25.h"

#include "utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day25_main(void) {
    char* input = file_to_string("./src/day25/data/input.txt");
    printf("2015:d25p1 - %u\n", day25_part1(input));
    free(input);
}

typedef struct {
    int64_t* memo;
    uint16_t r, c;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    free(s->memo);
    free(s);
}

//sum from 1->n = n*(n+1)/2
//add col to get pos in diag, -1 for zero based idx
static uint32_t rc_to_zidx(uint16_t r, uint16_t c) {
    uint16_t d = r + c - 1;
    return ((d - 1) * d / 2) + c - 1;
}

static state* state_init(const char* input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate state\n");
        goto bad_exit;
    }

    char* row_pos = strstr(input, "row ");
    if (!row_pos || sscanf(row_pos, "row %hu, column %hu", &(s->r), &(s->c)) != 2) {
        fprintf(stderr, "failed to parse input\n");
        goto bad_exit;
    }

    s->memo = calloc(rc_to_zidx(s->r, s->c) + 1, sizeof(int64_t));
    if (!s->memo) {
        fprintf(stderr, "failed to allocate memo\n");
        goto bad_exit;
    }
    s->memo[rc_to_zidx(1, 1)] = 20151125;
    s->memo[rc_to_zidx(1, 2)] = 18749137;
    s->memo[rc_to_zidx(1, 3)] = 17289845;
    s->memo[rc_to_zidx(1, 4)] = 30943339;
    s->memo[rc_to_zidx(1, 5)] = 10071777;
    s->memo[rc_to_zidx(1, 6)] = 33511524;
    s->memo[rc_to_zidx(2, 1)] = 31916031;
    s->memo[rc_to_zidx(2, 2)] = 21629792;
    s->memo[rc_to_zidx(2, 3)] = 16929656;
    s->memo[rc_to_zidx(2, 4)] = 7726640;
    s->memo[rc_to_zidx(2, 5)] = 15514188;
    s->memo[rc_to_zidx(2, 6)] = 4041754;
    s->memo[rc_to_zidx(3, 1)] = 16080970;
    s->memo[rc_to_zidx(3, 2)] = 8057251;
    s->memo[rc_to_zidx(3, 3)] = 1601130;
    s->memo[rc_to_zidx(3, 4)] = 7981243;
    s->memo[rc_to_zidx(3, 5)] = 11661866;
    s->memo[rc_to_zidx(3, 6)] = 16474243;
    s->memo[rc_to_zidx(4, 1)] = 24592653;
    s->memo[rc_to_zidx(4, 2)] = 32451966;
    s->memo[rc_to_zidx(4, 3)] = 21345942;
    s->memo[rc_to_zidx(4, 4)] = 9380097;
    s->memo[rc_to_zidx(4, 5)] = 10600672;
    s->memo[rc_to_zidx(4, 6)] = 31527494;
    s->memo[rc_to_zidx(5, 1)] = 77061;
    s->memo[rc_to_zidx(5, 2)] = 17552253;
    s->memo[rc_to_zidx(5, 3)] = 28094349;
    s->memo[rc_to_zidx(5, 4)] = 6899651;
    s->memo[rc_to_zidx(5, 5)] = 9250759;
    s->memo[rc_to_zidx(5, 6)] = 31663883;
    s->memo[rc_to_zidx(6, 1)] = 33071741;
    s->memo[rc_to_zidx(6, 2)] = 6796745;
    s->memo[rc_to_zidx(6, 3)] = 25397450;
    s->memo[rc_to_zidx(6, 4)] = 24659492;
    s->memo[rc_to_zidx(6, 5)] = 1534922;
    s->memo[rc_to_zidx(6, 6)] = 27995004;

    return s;
bad_exit:
    state_free(s);
    exit(1);
}

uint32_t day25_part1(const char* input) {
    state* s = state_init(input);
    uint32_t tgt = rc_to_zidx(s->r, s->c);

    for (uint32_t i = 1; i <= tgt; ++i) {
        int64_t res = (s->memo[i - 1] * 252533) % 33554393;
        assert(res < UINT32_MAX);

        if (i > 1 && s->memo[i] != 0) {
            assert(res == s->memo[i]);
        }
        s->memo[i] = res;
    }
    uint32_t out = (uint32_t)s->memo[tgt];
    state_free(s);
    return out;
}
