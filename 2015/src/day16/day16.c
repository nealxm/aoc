#include "day16.h"

#include "utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day16_main(void) {
    char** input = file_to_array("./src/day16/data/input.txt");
    printf("2015:d16p1 - %hu\n", day16_part1((const char* const*)input));
    printf("2015:d16p2 - %hu\n", day16_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    uint8_t children, cats, samoyeds, pomeranians, akitas, vizslas, goldfish, trees, cars, perfumes;
} sig;

typedef struct {
    sig** sigs;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (sig** sg = s->sigs; *sg; ++sg) {
        free(*sg);
    }
    free((void*)s->sigs);
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    s->sigs = (sig**)calloc(500, sizeof(sig*));
    if (!s || !s->sigs) {
        fprintf(stderr, "failed to allocate memory for state or sigs\n");
        goto bad_exit;
    }

    for (const char* const* l = input; *l; ++l) {
        s->sigs[l - input] = malloc(sizeof(sig));
        sig* curr = s->sigs[l - input];
        if (!curr) {
            fprintf(stderr, "failed to allocate memory for sig\n");
            goto bad_exit;
        }
        memset(curr, UINT8_MAX, sizeof(sig));

        char *children = strstr(*l, "children:"),
             *cats = strstr(*l, "cats:"),
             *samoyeds = strstr(*l, "samoyeds:"),
             *pomeranians = strstr(*l, "pomeranians:"),
             *akitas = strstr(*l, "akitas:"),
             *vizslas = strstr(*l, "vizslas:"),
             *goldfish = strstr(*l, "goldfish:"),
             *trees = strstr(*l, "trees:"),
             *cars = strstr(*l, "cars:"),
             *perfumes = strstr(*l, "perfumes:");

        if (children) {
            uint8_t val;
            assert(sscanf(children, "children: %hhu", &val) == 1);
            curr->children = val;
        }
        if (cats) {
            uint8_t val;
            assert(sscanf(cats, "cats: %hhu", &val) == 1);
            curr->cats = val;
        }
        if (samoyeds) {
            uint8_t val;
            assert(sscanf(samoyeds, "samoyeds: %hhu", &val) == 1);
            curr->samoyeds = val;
        }
        if (pomeranians) {
            uint8_t val;
            assert(sscanf(pomeranians, "pomeranians: %hhu", &val) == 1);
            curr->pomeranians = val;
        }
        if (akitas) {
            uint8_t val;
            assert(sscanf(akitas, "akitas: %hhu", &val) == 1);
            curr->akitas = val;
        }
        if (vizslas) {
            uint8_t val;
            assert(sscanf(vizslas, "vizslas: %hhu", &val) == 1);
            curr->vizslas = val;
        }
        if (goldfish) {
            uint8_t val;
            assert(sscanf(goldfish, "goldfish: %hhu", &val) == 1);
            curr->goldfish = val;
        }
        if (trees) {
            uint8_t val;
            assert(sscanf(trees, "trees: %hhu", &val) == 1);
            curr->trees = val;
        }
        if (cars) {
            uint8_t val;
            assert(sscanf(cars, "cars: %hhu", &val) == 1);
            curr->cars = val;
        }
        if (perfumes) {
            uint8_t val;
            assert(sscanf(perfumes, "perfumes: %hhu", &val) == 1);
            curr->perfumes = val;
        }
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

uint16_t day16_part1(const char* const* input) {
    state* s = state_init(input);
    uint8_t matches = 0;
    uint16_t out = 0;

    for (sig** sg = s->sigs; *sg; ++sg) {
        if (
            ((*sg)->children == 3 || (*sg)->children == UINT8_MAX) &&
            ((*sg)->cats == 7 || (*sg)->cats == UINT8_MAX) &&
            ((*sg)->samoyeds == 2 || (*sg)->samoyeds == UINT8_MAX) &&
            ((*sg)->pomeranians == 3 || (*sg)->pomeranians == UINT8_MAX) &&
            ((*sg)->akitas == 0 || (*sg)->akitas == UINT8_MAX) &&
            ((*sg)->vizslas == 0 || (*sg)->vizslas == UINT8_MAX) &&
            ((*sg)->goldfish == 5 || (*sg)->goldfish == UINT8_MAX) &&
            ((*sg)->trees == 3 || (*sg)->trees == UINT8_MAX) &&
            ((*sg)->cars == 2 || (*sg)->cars == UINT8_MAX) &&
            ((*sg)->perfumes == 1 || (*sg)->perfumes == UINT8_MAX)
        ) {
            ++matches;
            out = (uint16_t)(sg - s->sigs + 1);
        }
    }
    state_free(s);
    assert(matches == 1);
    return out;
}

uint16_t day16_part2(const char* const* input) {
    state* s = state_init(input);
    uint8_t matches = 0;
    uint16_t out = 0;

    for (sig** sg = s->sigs; *sg; ++sg) {
        if (
            ((*sg)->children == 3 || (*sg)->children == UINT8_MAX) &&
            ((*sg)->cats > 7 || (*sg)->cats == UINT8_MAX) &&
            ((*sg)->samoyeds == 2 || (*sg)->samoyeds == UINT8_MAX) &&
            ((*sg)->pomeranians < 3 || (*sg)->pomeranians == UINT8_MAX) &&
            ((*sg)->akitas == 0 || (*sg)->akitas == UINT8_MAX) &&
            ((*sg)->vizslas == 0 || (*sg)->vizslas == UINT8_MAX) &&
            ((*sg)->goldfish < 5 || (*sg)->goldfish == UINT8_MAX) &&
            ((*sg)->trees > 3 || (*sg)->trees == UINT8_MAX) &&
            ((*sg)->cars == 2 || (*sg)->cars == UINT8_MAX) &&
            ((*sg)->perfumes == 1 || (*sg)->perfumes == UINT8_MAX)
        ) {
            ++matches;
            out = (uint16_t)(sg - s->sigs + 1);
        }
    }
    state_free(s);
    assert(matches == 1);
    return out;
}
