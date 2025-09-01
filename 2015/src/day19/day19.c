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
    printf("2015:d19p2 - %hu\n", day19_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    char **ins, **outs, **mols;
    uint16_t num_mol;
    char* start;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (char** i = s->ins; *i; ++i) {
        free(*i);
    }
    for (char** i = s->outs; *i; ++i) {
        free(*i);
    }
    for (char** i = s->mols; *i; ++i) {
        free(*i);
    }
    free((void*)s->ins);
    free((void*)s->outs);
    free((void*)s->mols);
    free(s->start);
    free(s);
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
    s->ins = (char**)calloc(n, sizeof(char*));
    s->outs = (char**)calloc(n, sizeof(char*));
    if (!s->ins || !s->outs) {
        fprintf(stderr, "failed to allocate memory for ins or outs or unique");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        char* delim = strstr(*l, " => ");

        if (!delim) {
            s->start = strdup(*l);
            continue;
        }
        uint8_t i = (uint8_t)(l - input);
        s->ins[i] = strndup(*l, (size_t)(delim - *l));
        s->outs[i] = strdup(delim + 4);
    }
    s->mols = (char**)calloc(n * strlen(s->start), sizeof(char*));
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

uint16_t day19_part1(const char* const* input) {
    state* s = state_init(input);
    char* tmp_mol = malloc(strlen(s->start));

    for (char** i = s->ins; *i; ++i) {
        ptrdiff_t n = i - s->ins;
        size_t in_len = strlen(*i);
        size_t out_len = strlen(s->outs[n]);

        char* c = s->start;
        while ((c = strstr(c, *i)) != nullptr) {
            ptrdiff_t bef_len = c - s->start;

            strncpy(tmp_mol, s->start, bef_len);
            strcpy(tmp_mol + bef_len, s->outs[n]);
            strcpy(tmp_mol + bef_len + out_len, c + in_len);
            tmp_mol[strlen(s->start) - in_len + out_len] = '\0';

            bool found = false;
            char** j = s->mols;
            while (*j) {
                if (!strcmp(*j, tmp_mol)) {
                    found = true;
                    break;
                }
                ++j;
            }
            if (!found) {
                *j = strdup(tmp_mol);
                ++(s->num_mol);
            }
            ++c;
        }
    }
    uint16_t out = s->num_mol;
    state_free(s);
    return out;
}

uint16_t day19_part2(const char* const* input) {
    state* s = state_init(input);

    state_free(s);
    return 0;
}
