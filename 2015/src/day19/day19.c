#include "day19.h"

#include "utils.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day19_main(void) {
    char** input = file_to_array("./src/day19/data/input.txt");
    printf("2015:d19p1 - %hu\n", day19_part1((const char* const*)input));
    printf("2015:d19p2 - %hhu\n", day19_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    char *in, *out;
} rule;

typedef struct {
    rule** rules;
    char* start;
    uint16_t num_mol, max_mol;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (rule** r = s->rules; *r; ++r) {
        free((*r)->in);
        free((*r)->out);
        free(*r);
    }
    free((void*)s->rules);
    free(s->start);
    free(s);
}

static int compare_descend(const void* a, const void* b) {
    const rule* rule_a = *(const rule* const*)a;
    const rule* rule_b = *(const rule* const*)b;

    size_t len_a = strlen(rule_a->out);
    size_t len_b = strlen(rule_b->out);
    if (len_b != len_a) {
        return (int)len_b - (int)len_a;
    }
    return strcmp(rule_a->out, rule_b->out);
}

static state* state_init(const char* const* input) {
    uint8_t n = 0;
    for (const char* const* l = input; *l; ++l) {
        ++n;
    }
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate memory for state");
        goto bad_exit;
    }
    s->rules = (rule**)calloc(n, sizeof(rule*));
    if (!s->rules) {
        fprintf(stderr, "failed to allocate memory for rules");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        char* delim = strstr(*l, " => ");

        if (!delim) {
            s->start = strdup(*l);
            continue;
        }
        s->rules[l - input] = malloc(sizeof(rule));
        if (!s->rules[l - input]) {
            fprintf(stderr, "failed to allocate rule");
            goto bad_exit;
        }

        *(s->rules[l - input]) = (rule){
            .in = strndup(*l, (size_t)(delim - *l)),
            .out = strdup(delim + 4)
        };
    }
    qsort((void*)s->rules, n - 1, sizeof(rule*), compare_descend);
    s->max_mol = (uint16_t)strlen(s->start) * 4;
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

uint16_t day19_part1(const char* const* input) {
    state* s = state_init(input);
    char* tmp_mol = calloc(s->max_mol, sizeof(char));
    char** mols = (char**)calloc(s->max_mol, sizeof(char*));
    uint16_t out = 0;

    for (rule** r = s->rules; *r; ++r) {
        size_t in_len = strlen((*r)->in);
        size_t out_len = strlen((*r)->out);

        char* c = s->start;
        while ((c = strstr(c, (*r)->in)) != nullptr) {
            ptrdiff_t bef_len = c - s->start;

            strncpy(tmp_mol, s->start, bef_len);
            strcpy(tmp_mol + bef_len, (*r)->out);
            strcpy(tmp_mol + bef_len + out_len, c + in_len);
            tmp_mol[strlen(s->start) - in_len + out_len] = '\0';

            bool found = false;
            char** j = mols;
            while (*j) {
                if (!strcmp(*j, tmp_mol)) {
                    found = true;
                    break;
                }
                ++j;
            }
            if (!found) {
                *j = strdup(tmp_mol);
                ++out;
            }
            ++c;
        }
    }
    state_free(s);
    free(tmp_mol);
    for (char** j = mols; *j; ++j) {
        free(*j);
    }
    free((void*)mols);
    return out;
}

static uint8_t find_target(state* s, uint8_t iter, char* curr_mol) {
    if (strcmp(curr_mol, "e") == 0) {
        return iter;
    }
    char* tmp_mol = calloc(s->max_mol, sizeof(char));

    for (rule** r = s->rules; *r; ++r) {
        size_t out_len = strlen((*r)->out);
        size_t in_len = strlen((*r)->in);
        size_t new_len = strlen(curr_mol) - out_len + in_len;
        if (out_len > strlen(curr_mol) || new_len >= s->max_mol) {
            continue;
        }

        char* c = curr_mol;
        while ((c = strstr(c, (*r)->out)) != nullptr) {
            ptrdiff_t bef_len = c - curr_mol;

            strncpy(tmp_mol, curr_mol, bef_len);
            strcpy(tmp_mol + bef_len, (*r)->in);
            strcpy(tmp_mol + bef_len + in_len, c + out_len);
            tmp_mol[new_len] = '\0';

            uint8_t res = find_target(s, iter + 1, tmp_mol);
            return res;
        }
    }
    free(tmp_mol);
    return UINT8_MAX;
}

uint8_t day19_part2(const char* const* input) {
    state* s = state_init(input);
    char* tmp_mol = calloc(s->max_mol, sizeof(char));
    strcpy(tmp_mol, s->start);

    uint8_t out = find_target(s, 0, tmp_mol);
    state_free(s);
    free(tmp_mol);
    return out;
}
