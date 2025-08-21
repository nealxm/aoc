#include "day15.h"

#include "utils.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day15_main(void) {
    char** input = file_to_array("./src/day15/data/input.txt");
    printf("2015:d15p1 - %u\n", day15_part1((const char* const*)input));
    printf("2015:d15p2 - %u\n", day15_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    int8_t cap, dura, flav, tex, cals;
} ing;

typedef struct {
    ing** ings;
    uint8_t num_ing;
    uint8_t* amts;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    if (s->ings) {
        for (ing** i = s->ings; *i; ++i) {
            free((*i));
        }
        free((void*)s->ings);
    }
    free(s->amts);
    free(s);
}

static state* state_init(const char* const* input) {
    uint8_t n = 0;
    for (const char* const* l = input; *l; ++l) {
        ++n;
    }
    state* s = malloc(sizeof(state));
    s->ings = (ing**)calloc(n + 1, sizeof(ing*));
    s->amts = calloc(n, sizeof(uint8_t));
    s->num_ing = n;
    if (!s || !s->ings || !s->amts) {
        fprintf(stderr, "failed to allocate state or ings or amts\n");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        int8_t cap_tmp, dura_tmp, flav_tmp, tex_tmp, cals_tmp;

        if (
            sscanf(*l, "%*s capacity %hhd, durability %hhd, flavor %hhd, texture %hhd, calories %hhd", //
                   &cap_tmp, &dura_tmp, &flav_tmp, &tex_tmp, &cals_tmp) != 5
        ) {
            fprintf(stderr, "failed to parse line %s\ncap: %hhd", *l, cap_tmp);
            goto bad_exit;
        }
        ptrdiff_t i = l - input;

        s->ings[i] = malloc(sizeof(ing));
        if (!s->ings[i]) {
            fprintf(stderr, "failed to allocate ingredient\n");
            goto bad_exit;
        }
        *(s->ings[i]) = (ing){
            .cap = cap_tmp,
            .dura = dura_tmp,
            .flav = flav_tmp,
            .tex = tex_tmp,
            .cals = cals_tmp
        };
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

static uint32_t calc_score(const state* s) {
    int16_t cap = 0, dura = 0, flav = 0, tex = 0;

    for (ing** i = s->ings; *i; ++i) {
        uint8_t amt = s->amts[i - s->ings];

        cap += amt * (*i)->cap;
        dura += amt * (*i)->dura;
        flav += amt * (*i)->flav;
        tex += amt * (*i)->tex;
    }
    return (cap >= 0 && dura >= 0 && flav >= 0 && tex >= 0) ? (uint32_t)(cap * dura * flav * tex) : 0;
}

static int16_t calc_cals(const state* s) {
    int16_t cals = 0;

    for (ing** i = s->ings; *i; ++i) {
        cals += s->amts[i - s->ings] * (*i)->cals;
    }
    return cals;
}

static uint32_t find_best_comb(state* s, uint8_t ing_curr, uint8_t tsps, bool chk_cals) {
    if (ing_curr == s->num_ing - 1) {
        s->amts[ing_curr] = tsps;
        if (chk_cals && calc_cals(s) != 500) {
            return 0;
        }
        return calc_score(s);
    }
    uint32_t max = 0;

    for (uint8_t i = 0; i <= tsps; ++i) {
        s->amts[ing_curr] = i;

        uint32_t res = find_best_comb(s, ing_curr + 1, tsps - i, chk_cals);
        max = res > max ? res : max;
    }
    return max;
}

uint32_t day15_part1(const char* const* input) {
    state* s = state_init(input);
    uint32_t out = find_best_comb(s, 0, 100, false);
    state_free(s);
    return out;
}

uint32_t day15_part2(const char* const* input) {
    state* s = state_init(input);
    uint32_t out = find_best_comb(s, 0, 100, true);
    state_free(s);
    return out;
}
