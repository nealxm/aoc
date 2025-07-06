#include "day03.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day03_main(void) {
    char* input = file_to_string("./src/day03/data/input.txt");
    printf("2015:d03p1 - %d\n", day03_part1(input));
    printf("2015:d03p2 - %d\n", day03_part2(input));
    free(input);
}

uint16_t day03_part1(const char* input) {
    state*   s = state_init(input);
    uint16_t r = 0;

    for (const char* d = s->dirs; *d != '\0'; ++d) {
        if (pos_move(&s->curr, *d) != 0
            || visited_add(&s->visited, &s->visited_len, &s->curr) != 0) {
            goto cleanup;
        }
    }
    r = s->visited_len;

cleanup:
    state_free(s);
    if (r == 0) {
        exit(1);
    }
    return r;
}

uint16_t day03_part2(const char* input) {
    state*   s = state_init(input);
    uint16_t r = 0;

    for (uint16_t i = 0; s->dirs[i] != '\0'; ++i) {
        pos* curr_adj = (i % 2 == 0) ? &s->curr : &s->curr_r;

        if (pos_move(curr_adj, s->dirs[i]) != 0
            || visited_add(&s->visited, &s->visited_len, curr_adj) != 0) {
            goto cleanup;
        }
    }
    r = s->visited_len;

cleanup:
    state_free(s);
    if (r == 0) {
        exit(1);
    }
    return r;
}

state* state_init(const char* input) {
    state* s = malloc(sizeof(state));

    *s = (state){
        .dirs        = input,
        .curr        = {0, 0},
        .curr_r      = {0, 0},
        .visited_len = 1,
        .visited     = malloc(sizeof(pos)),
    };
    s->visited[0] = (pos){0, 0};
    return s;
}

void state_free(state* s) {
    free(s->visited);
    free(s);
}

uint8_t pos_move(pos* p, char d) {
    switch (d) {
    case '^': ++p->y; break;
    case '>': ++p->x; break;
    case 'v': --p->y; break;
    case '<': --p->x; break;
    default : fprintf(stderr, "invalid direction '%c'\n", d); return 1;
    }
    return 0;
}

bool pos_equal(const pos* a, const pos* b) {
    return (bool)(a->x == b->x && a->y == b->y);
}

uint8_t visited_add(pos** v, uint16_t* l, const pos* n) {
    for (uint16_t i = 0; i < *l; ++i) {
        if (pos_equal(&(*v)[i], n)) {
            return 0;
        }
    }
    pos* visited_new = realloc(*v, sizeof(pos) * (size_t)(++(*l)));
    if (!visited_new) {
        fprintf(stderr, "could not reallocate memory for new visited\n");
        return 1;
    }
    *v           = visited_new;
    (*v)[*l - 1] = *n;
    return 0;
}
