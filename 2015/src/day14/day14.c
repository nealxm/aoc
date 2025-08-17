#include "day14.h"

#include "utils.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day14_main(void) {
    char** input = file_to_array("./src/day14/data/input.txt");
    printf("2015:d14p1 - %hu\n", day14_part1(input));
    printf("2015:d14p2 - %hu\n", day14_part2(input));
    free_array((void**)input);
}

typedef struct {
    uint8_t rate, dur, rest;
} racer;

typedef struct {
    racer** racers;
} state;

static void free_state(state* s) {
    if (!s) {
        return;
    }
    for (racer** r = s->racers; *r; ++r) {
        free(*r);
    }
    free((void*)s->racers);
    free(s);
}

static state* state_init(char** input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate memory for state\n");
        exit(1);
    }
    uint8_t n = 0;
    for (char** l = input; *l; ++l) {
        ++n;
    }
    s->racers = (racer**)malloc(1 + (n * sizeof(racer*)));
    if (!s->racers) {
        fprintf(stderr, "failed to allocate memory for racers\n");
        free_state(s);
        exit(1);
    }
    for (char** l = input; *l; ++l) {
        ptrdiff_t i = l - input;
        uint8_t rate_tmp, dur_tmp, rest_tmp;

        if (sscanf(
                *l,
                "%*s can fly %hhu km/s for %hhu seconds, but then must rest for %hhu seconds.",
                &rate_tmp,
                &dur_tmp,
                &rest_tmp
            ) != 3) {
            fprintf(stderr, "failed to parse racer: %s\n", *l);
            free_state(s);
            exit(1);
        }
        s->racers[i] = malloc(sizeof(racer));
        if (!s->racers[i]) {
            fprintf(stderr, "failed to allocate memory for racer\n");
            free_state(s);
            exit(1);
        }
        *(s->racers[i]) = (racer){.rate = rate_tmp, .dur = dur_tmp, .rest = rest_tmp};
    }
    s->racers[n] = nullptr;
    return s;
}

uint16_t day14_part1(char** input) {
    state* s = state_init(input);
    uint16_t max = 0;

    for (racer** r = s->racers; *r; ++r) {
        uint16_t cycle_time = (*r)->dur + (*r)->rest;
        uint16_t cycle_dist = (*r)->rate * (*r)->dur;

        uint16_t cycles = 2503 / cycle_time;
        uint16_t curr_dist = cycles * cycle_dist;
        uint16_t time_left = 2503 % cycle_time;
        assert(time_left + (cycles * cycle_time) == 2503);

        if (time_left > 0) {
            curr_dist += (*r)->rate * (time_left < (*r)->dur ? time_left : (*r)->dur);
        }
        max = max > curr_dist ? max : curr_dist;
    }
    free_state(s);
    return max;
}

uint16_t day14_part2(char** input) {
    state* s = state_init(input);
    uint16_t max = 0;

    for (uint16_t i = 0; i < 2503; ++i) {
        for (racer** r = s->racers; *r; ++r) {
        }
    }
    free_state(s);
    return max;
}
