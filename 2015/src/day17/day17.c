#include "day17.h"

#include "utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day17_main(void) {
    char** input = file_to_array("./src/day17/data/input.txt");
    printf("2015:d17p1 - %hu\n", day17_part1((const char* const*)input));
    printf("2015:d17p2 - %hu\n", day17_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    uint8_t cap;
} bucket;

typedef struct {
    bucket** bucks;
    uint8_t num_bucks, min_bucks;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (bucket** b = s->bucks; *b; ++b) {
        free(*b);
    }
    free((void*)s->bucks);
    free(s);
}

static state* state_init(const char* const* input) {
    uint8_t n = 0;
    for (const char* const* l = input; *l; ++l) {
        ++n;
    }
    state* s = malloc(sizeof(state));
    s->num_bucks = n;
    s->min_bucks = UINT8_MAX;
    s->bucks = (bucket**)calloc(n + 1, sizeof(bucket*));
    if (!s || !s->bucks) {
        fprintf(stderr, "failed to allocate state\n");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        s->bucks[l - input] = malloc(sizeof(bucket));
        bucket* curr = s->bucks[l - input];
        if (!curr) {
            fprintf(stderr, "failed to allocate bucket\n");
            goto bad_exit;
        }
        int32_t val = atoi(*l);
        assert(val < UINT8_MAX);
        curr->cap = (uint8_t)val;
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

static uint16_t count_combs(state* s, uint16_t sum_curr, uint8_t curr, uint8_t len) {
    if (sum_curr == 150) {
        s->min_bucks = len < s->min_bucks ? len : s->min_bucks;
        return 1;
    } else if (sum_curr > 150) {
        return 0;
    }
    uint16_t out = 0;

    for (uint8_t i = curr; i < s->num_bucks; ++i) {
        out += count_combs(s, sum_curr + s->bucks[i]->cap, i + 1, len + 1);
    }
    return out;
}

uint16_t day17_part1(const char* const* input) {
    state* s = state_init(input);
    uint16_t out = count_combs(s, 0, 0, 0);
    state_free(s);
    return out;
}

static uint16_t count_len(state* s, uint16_t sum_curr, uint8_t curr, uint8_t len) {
    if (sum_curr == 150 && len == s->min_bucks) {
        return 1;
    } else if (sum_curr > 150) {
        return 0;
    }
    uint16_t out = 0;

    for (uint8_t i = curr; i < s->num_bucks; ++i) {
        out += count_len(s, sum_curr + s->bucks[i]->cap, i + 1, len + 1);
    }
    return out;
}

uint16_t day17_part2(const char* const* input) {
    state* s = state_init(input);
    count_combs(s, 0, 0, 0);
    uint16_t out = count_len(s, 0, 0, 0);
    state_free(s);
    return out;
}
