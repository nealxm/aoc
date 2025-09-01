#include "day13.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day13_main(void) {
    char** input = file_to_array("./src/day13/data/input.txt");
    printf("2015:d13p1 - %hd\n", day13_part1((const char* const*)input));
    printf("2015:d13p2 - %hd\n", day13_part2((const char* const*)input));
    free_array((void**)input);
}

typedef enum {
    lose,
    gain
} rule_kind;

typedef struct {
    char *subj, *neig;
    rule_kind kind;
    uint8_t mod;
} rule;

typedef struct {
    rule** rules;
    char** people;
    uint8_t num_ppl;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (rule** r = s->rules; *r; ++r) {
        free((*r)->subj);
        free((*r)->neig);
    }
    free((void*)s->rules);

    for (char** p = s->people; *p; ++p) {
        free((*p));
    }
    free((void*)s->people);
    free(s);
}

static state* state_init(const char* const* input) {
    uint8_t lines = 0;
    for (const char* const* l = input; *l; ++l) {
        ++lines;
    }
    state* s = malloc(sizeof(state));

    if (!s) {
        fprintf(stderr, "failed to allocate memory for state\n");
        exit(1);
    }
    s->rules = (rule**)calloc(lines + 1, sizeof(rule*));
    s->people = nullptr;
    s->num_ppl = 0;

    if (!s->rules) {
        fprintf(stderr, "failed to allocate memory for rules\n");
        state_free(s);
        exit(1);
    }

    for (const char* const* l = input; *l; ++l) {
        rule* new_rule = malloc(sizeof(rule));
        if (!new_rule) {
            fprintf(stderr, "failed to allocate memory for rule\n");
            state_free(s);
            exit(1);
        }
        char subj_tmp[16], neig_tmp[16];
        uint8_t mod_tmp;

        if (
            sscanf(*l, "%s would gain %hhu happiness units by sitting next to %[^.].", //
                   subj_tmp, &mod_tmp, neig_tmp) == 3
        ) {
            new_rule->kind = gain;
        } else if (
            sscanf(*l, "%s would lose %hhu happiness units by sitting next to %[^.].", //
                   subj_tmp, &mod_tmp, neig_tmp) == 3
        ) {
            new_rule->kind = lose;
        }
        new_rule->subj = strdup(subj_tmp);
        new_rule->neig = strdup(neig_tmp);
        new_rule->mod = mod_tmp;
        s->rules[l - input] = new_rule;

        bool subj_found = false, neig_found = false;
        for (uint8_t j = 0; j < s->num_ppl; ++j) {
            if (strcmp(s->people[j], new_rule->subj) == 0) {
                subj_found = true;
            }
            if (strcmp(s->people[j], new_rule->neig) == 0) {
                neig_found = true;
            }
        }
        if (subj_found && neig_found) {
            continue;
        }
        uint8_t cities_to_add = (!subj_found ? 1 : 0) + (!neig_found ? 1 : 0);

        char** tmp = (char**)realloc((void*)s->people, (s->num_ppl + cities_to_add + 1) * sizeof(char*));
        if (!tmp) {
            fprintf(stderr, "failed to reallocate memory for people\n");
            state_free(s);
            exit(1);
        }
        s->people = tmp;

        if (!subj_found) {
            s->people[s->num_ppl++] = strdup(new_rule->subj);
        }
        if (!neig_found) {
            s->people[s->num_ppl++] = strdup(new_rule->neig);
        }
        s->people[s->num_ppl] = nullptr;
    }
    return s;
}

static int8_t find_rule(state* s, uint8_t subj, uint8_t neig) {
    if (strcmp(s->people[subj], "me") == 0 || strcmp(s->people[neig], "me") == 0) {
        return 0;
    }
    for (rule** r = s->rules; *r; ++r) {
        if (strcmp(s->people[subj], (*r)->subj) == 0 && strcmp(s->people[neig], (*r)->neig) == 0) {
            return (*r)->kind == gain ? (int8_t)(*r)->mod : (int8_t)-(*r)->mod;
        }
    }
    return 0;
}

static int16_t calc_happ(state* s, uint8_t* order) {
    int16_t total = 0;
    uint8_t n = s->num_ppl;

    for (uint8_t i = 0; i < n; ++i) {
        uint8_t l = i == 0 ? n - 1 : i - 1;
        uint8_t r = (i == n - 1) ? 0 : i + 1;

        total += find_rule(s, order[i], order[l]) + find_rule(s, order[i], order[r]);
    }
    return total;
}

static int16_t find_max_happ(state* s, uint8_t* curr_order, uint8_t curr_size) {
    if (curr_size == s->num_ppl) {
        return calc_happ(s, curr_order);
    }
    int16_t max = INT16_MIN;

    for (uint8_t i = 0; i < s->num_ppl; ++i) {
        for (uint8_t j = 0; j < curr_size; ++j) {
            if (curr_order[j] == i) {
                goto outer; //i is potential next; skip if it appears anywhere in curr order
            }
        }
        curr_order[curr_size] = i;
        int16_t res = find_max_happ(s, curr_order, curr_size + 1);
        max = res > max ? res : max;
    outer:
    }
    return max;
}

int16_t day13_part1(const char* const* input) {
    state* s = state_init(input);
    uint8_t* order = calloc(s->num_ppl, sizeof(uint8_t));
    if (!order) {
        fprintf(stderr, "failed to allocate memory for order\n");
        state_free(s);
        exit(1);
    }
    int16_t out = find_max_happ(s, order, 0);
    state_free(s);
    free(order);
    return out;
}

int16_t day13_part2(const char* const* input) {
    state* s = state_init(input);
    char** tmp = (char**)realloc((void*)s->people, (s->num_ppl + 2) * sizeof(char*));
    if (!tmp) {
        fprintf(stderr, "failed to reallocate memory for people\n");
        state_free(s);
        exit(1);
    }
    s->people = tmp;
    s->people[s->num_ppl++] = strdup("me");
    s->people[s->num_ppl] = nullptr;

    uint8_t* order = calloc(s->num_ppl, sizeof(uint8_t));
    if (!order) {
        fprintf(stderr, "failed to allocate memory for order\n");
        state_free(s);
        exit(1);
    }
    int16_t out = find_max_happ(s, order, 0);
    state_free(s);
    free(order);
    return out;
}
