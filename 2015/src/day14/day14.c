#include "day14.h"

#include "utils.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day14_main(void) {
    char** input = file_to_array("./src/day14/data/input.txt");
    printf("2015:d14p1 - %hu\n", day14_part1((const char* const*)input));
    printf("2015:d14p2 - %hu\n", day14_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    uint8_t rate, dur, rest;
} racer;

typedef struct {
    racer** racers;
    uint8_t num_racers;
    uint16_t *dists, *points;
    uint8_t* state_time;
    bool* resting;
} state;

static void free_state(state* s) {
    if (!s) {
        return;
    }
    for (racer** r = s->racers; *r; ++r) {
        free(*r);
    }
    free((void*)s->racers);
    free(s->dists);
    free(s->points);
    free(s->state_time);
    free(s->resting);
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate memory for state\n");
        exit(1);
    }
    uint8_t n = 0;
    for (const char* const* l = input; *l; ++l) {
        ++n;
    }
    s->racers = (racer**)malloc(1 + (n * sizeof(racer*)));
    if (!s->racers) {
        fprintf(stderr, "failed to allocate memory for racers\n");
        free_state(s);
        exit(1);
    }
    for (const char* const* l = input; *l; ++l) {
        ptrdiff_t i = l - input;
        uint8_t rate_tmp, dur_tmp, rest_tmp;

        if (
            sscanf(*l, "%*s can fly %hhu km/s for %hhu seconds, but then must rest for %hhu seconds.", //
                   &rate_tmp, &dur_tmp, &rest_tmp) != 3
        ) {
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
        *(s->racers[i]) = (racer){
            .rate = rate_tmp,
            .dur = dur_tmp,
            .rest = rest_tmp
        };
    }
    s->racers[n] = nullptr;

    s->num_racers = n;
    s->dists = calloc(n, sizeof(uint16_t));
    s->points = calloc(n, sizeof(uint16_t));
    s->state_time = calloc(n, sizeof(uint8_t));
    s->resting = calloc(n, sizeof(bool));
    if (!s->dists || !s->points || !s->state_time || !s->resting) {
        fprintf(stderr, "failed to allocate dists, state_time, or resting");
        free_state(s);
        exit(1);
    }
    return s;
}

uint16_t day14_part1(const char* const* input) {
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

uint16_t day14_part2(const char* const* input) {
    state* s = state_init(input);

    for (uint16_t i = 0; i < 2503; ++i) {
        for (uint8_t n = 0; n < s->num_racers; ++n) {

            if (!s->resting[n]) {
                s->dists[n] += s->racers[n]->rate;
            }
            ++(s->state_time[n]);

            if (!s->resting[n] && s->state_time[n] >= s->racers[n]->dur) {
                s->resting[n] = true;
                s->state_time[n] = 0;
            } else if (s->resting[n] && s->state_time[n] >= s->racers[n]->rest) {
                s->resting[n] = false;
                s->state_time[n] = 0;
            }
        }
        uint16_t max_dist = 0;
        for (uint8_t n = 0; n < s->num_racers; ++n) {
            if (s->dists[n] > max_dist) {
                max_dist = s->dists[n];
            }
        }
        for (uint8_t n = 0; n < s->num_racers; ++n) {
            if (s->dists[n] == max_dist) {
                ++(s->points[n]);
            }
        }
    }
    uint16_t max = 0;
    for (uint8_t n = 0; n < s->num_racers; ++n) {
        max = max > s->points[n] ? max : s->points[n];
    }
    free_state(s);
    return max;
}
