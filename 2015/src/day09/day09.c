#include "day09.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day09_main(void) {
    char** input = file_to_array("./src/day09/data/input.txt");
    printf("2015:d09p1 - %hu\n", day09_part1((const char* const*)input));
    printf("2015:d09p2 - %hu\n", day09_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    char *org, *dst;
    uint16_t dist;
} route;

typedef struct {
    route** routes;
    char** cities;
    uint8_t num_cities;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    if (s->routes) {
        for (route** r = s->routes; *r; ++r) {
            free((*r)->org);
            free((*r)->dst);
            free(*r);
        }
        free((void*)s->routes);
    }
    if (s->cities) {
        free_array((void**)s->cities);
    }
    free(s);
}

static state* state_init(const char* const* input) {
    uint8_t lines = 0;
    for (const char* const* l = input; *l; ++l) {
        ++lines;
    }
    state* s = calloc(1, sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate memory for state\n");
        state_free(s);
        exit(1);
    }
    s->routes = (route**)calloc(lines + 1, sizeof(route*));
    if (!s->routes) {
        fprintf(stderr, "failed to allocate memory for routes\n");
        state_free(s);
        exit(1);
    }
    s->cities = (char**)calloc(1, sizeof(char*));
    if (!s->cities) {
        fprintf(stderr, "failed to allocate memory for cities\n");
        state_free(s);
        exit(1);
    }

    for (const char* const* l = input; *l; ++l) {
        char org_tmp[16], dst_tmp[16];
        uint16_t dist_tmp;
        sscanf(*l, "%s to %s = %hu", org_tmp, dst_tmp, &dist_tmp);

        route* r = malloc(sizeof(route));
        r->org = strdup(org_tmp);
        r->dst = strdup(dst_tmp);
        r->dist = dist_tmp;
        s->routes[l - input] = r;

        bool org_found = false, dst_found = false;
        for (uint8_t j = 0; j < s->num_cities; ++j) {
            if (strcmp(s->cities[j], r->org) == 0) {
                org_found = true;
            }
            if (strcmp(s->cities[j], r->dst) == 0) {
                dst_found = true;
            }
        }
        if (org_found && dst_found) {
            continue;
        }
        uint8_t cities_to_add = (!org_found ? 1 : 0) + (!dst_found ? 1 : 0);
        char** tmp = (char**)realloc((void*)s->cities, (s->num_cities + cities_to_add + 1) * sizeof(char*));
        if (!tmp) {
            fprintf(stderr, "failed to allocate memory for cities\n");
            state_free(s);
            exit(1);
        }
        s->cities = tmp;

        if (!org_found) {
            s->cities[s->num_cities++] = strdup(r->org);
        }
        if (!dst_found) {
            s->cities[s->num_cities++] = strdup(r->dst);
        }
        s->cities[s->num_cities] = nullptr;
    }
    return s;
}

static uint16_t find_dist(state* s, uint8_t org, uint8_t dst) {
    for (route** r = s->routes; *r; ++r) {
        if ((strcmp((*r)->org, s->cities[org]) == 0 && (strcmp((*r)->dst, s->cities[dst]) == 0)) ||
            (strcmp((*r)->org, s->cities[dst]) == 0 && (strcmp((*r)->dst, s->cities[org]) == 0))) {
            return (*r)->dist;
        }
    }
    return UINT16_MAX;
}

static uint16_t find_best_route(state* s, bool longest, uint16_t curr_dist, uint8_t curr_visited, uint8_t* curr_route) {
    if (curr_visited == s->num_cities) {
        return curr_dist;
    }
    uint16_t best_dist = longest ? 0 : UINT16_MAX;

    for (uint8_t i = 0; i < s->num_cities; ++i) {
        for (uint8_t j = 0; j < curr_visited; ++j) {
            if (curr_route[j] == i) {
                goto outer;
            }
        }
        curr_route[curr_visited] = i;
        uint16_t res;

        if (curr_visited == 0) {
            res = find_best_route(s, longest, curr_dist, curr_visited + 1, curr_route);
            goto best_res;
        }
        uint8_t curr_city = curr_route[curr_visited - 1];
        uint16_t next_dist = find_dist(s, curr_city, i);
        if (next_dist == UINT16_MAX) {
            goto outer;
        }
        res = find_best_route(s, longest, curr_dist + next_dist, curr_visited + 1, curr_route);

    best_res:
        if (longest) {
            if (res > best_dist) {
                best_dist = res;
            }
        } else {
            if (res < best_dist) {
                best_dist = res;
            }
        }
    outer:
    }
    return best_dist;
}

uint16_t day09_part1(const char* const* input) {
    state* s = state_init(input);
    uint8_t* curr_route = calloc(s->num_cities, sizeof(uint8_t));
    if (!curr_route) {
        fprintf(stderr, "failed to allocate memory for route\n");
        state_free(s);
        exit(1);
    }
    uint16_t out = find_best_route(s, false, 0, 0, curr_route);
    state_free(s);
    free(curr_route);
    return out;
}

uint16_t day09_part2(const char* const* input) {
    state* s = state_init(input);
    uint8_t* curr_route = calloc(s->num_cities, sizeof(uint8_t));
    if (!curr_route) {
        fprintf(stderr, "failed to allocate memory for route\n");
        state_free(s);
        exit(1);
    }
    uint16_t out = find_best_route(s, true, 0, 0, curr_route);
    state_free(s);
    free(curr_route);
    return out;
}
