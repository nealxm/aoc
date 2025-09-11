#include "day24.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day24_main(void) {
    char** input = file_to_array("./src/day24/data/input.txt");
    printf("2015:d24p1 - %lld\n", day24_part1((const char* const*)input));
    printf("2015:d24p2 - %lld\n", day24_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    uint8_t num_pkg;
    uint8_t *pkgs, *p_g1;
    bool* used;
    uint16_t weight;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    free(s->pkgs);
    free(s->p_g1);
    free(s->used);
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate state");
        goto bad_exit;
    }
    s->num_pkg = 0;
    s->weight = 0;

    for (const char* const* l = input; *l; ++l) {
        ++s->num_pkg;
    }
    s->pkgs = calloc(s->num_pkg + 1, sizeof(uint8_t));
    s->p_g1 = calloc(s->num_pkg + 1, sizeof(uint8_t));
    s->used = calloc(s->num_pkg + 1, sizeof(bool));
    if (!s->pkgs || !s->p_g1 || !s->used) {
        fprintf(stderr, "failed to allocate arrs");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        uint8_t val = (uint8_t)atoi(*l);
        s->pkgs[l - input] = val;
        s->weight += val;
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

//array, num elements, max val
static bool next_comb(uint8_t* a, uint8_t k, uint8_t n) {
    for (int8_t i = k - 1; i >= 0; --i) {
        if (a[i] < n - k + i) { //max value at pos is max value - number of values we are using + index
            ++(a[i]);
            for (int8_t j = i + 1; j < k; ++j) { //update elements to the right of updated element lexicographically
                a[j] = a[j - 1] + 1;
            }
            return true;
        }
    }
    return false;
}

static bool subset_sum_exits(state* s, uint16_t tgt) {
    bool found[tgt + 1] = {};
    found[0] = true;

    for (uint8_t i = 0; i < s->num_pkg; ++i) {
        if (s->used[i]) {
            continue;
        }

        for (uint16_t j = tgt; j >= s->pkgs[i]; --j) {
            found[j] |= found[j - s->pkgs[i]];
        }
        if (found[tgt]) {
            return true;
        }
    }
    return found[tgt];
}

static int64_t balance_pkgs(state* s, uint8_t groups) {
    int64_t min_qe = INT64_MAX;
    uint16_t tgt = s->weight / groups;

    for (uint8_t k = 1; k <= s->num_pkg; ++k) {
        for (uint8_t i = 0; i < k; ++i) {
            s->p_g1[i] = i;
        }
        do {
            uint16_t pass_sum = 0;
            memset(s->used, false, s->num_pkg);

            for (uint8_t i = 0; i < k; ++i) {
                uint8_t j = s->p_g1[i];

                pass_sum += s->pkgs[j];
                s->used[j] = true;

                if (pass_sum > tgt) {
                    goto outer;
                }
            }
            if (pass_sum != tgt || !subset_sum_exits(s, tgt)) {
                continue;
            }

            int64_t qe = 1;
            for (uint8_t i = 0; i < k; ++i) {
                qe *= s->pkgs[s->p_g1[i]];
            }
            min_qe = qe < min_qe ? qe : min_qe;

        outer:
        } while (next_comb(s->p_g1, k, s->num_pkg));

        if (min_qe != INT64_MAX) {
            break;
        }
    }
    return min_qe;
}

int64_t day24_part1(const char* const* input) {
    state* s = state_init(input);
    int64_t out = balance_pkgs(s, 3);
    state_free(s);
    return out;
}

int64_t day24_part2(const char* const* input) {
    state* s = state_init(input);
    int64_t out = balance_pkgs(s, 4);
    state_free(s);
    return out;
}
