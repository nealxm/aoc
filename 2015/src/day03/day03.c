#include "day03.h"

#include "utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void day03_main(void) {
    char* input = file_to_string("./src/day03/data/input.txt");
    printf("2015:d03p1 - %d\n", day03_part1(input));
    printf("2015:d03p2 - %d\n", day03_part2(input));
    free(input);
}

int day03_part1(const char* input) {
    state* s = parse_input(input);
    for (const char* d = s->dirs; *d != '\0'; d++) {
        switch (*d) {
        case '^': s->curr.y++; break;
        case '>': s->curr.x++; break;
        case 'v': s->curr.y--; break;
        case '<': s->curr.x--; break;
        default : {
            fprintf(stderr, "invalid direction '%c'", *d);
            free(s->visited);
            free(s);
            exit(1);
        }
        }
        bool found = false;
        for (int v = 0; v < s->visited_len; v++) {
            if (pos_equal(s->visited[v], s->curr)) {
                found = true;
                break;
            }
        }
        if (!found) {
            pos* visited_new = realloc(s->visited, sizeof(pos) * (size_t)(s->visited_len + 1));
            if (!visited_new) {
                fprintf(stderr, "could not reallocate memory for new visited");
                free(s->visited);
                free(s);
                exit(1);
            }
            s->visited                     = visited_new;
            s->visited[s->visited_len - 1] = s->curr;
            s->visited_len++;
        }
    }
    int r = (int)s->visited_len;
    free(s->visited);
    free(s);
    return r;
}

int day03_part2(const char*) {
    return 0;
}

state* parse_input(const char* input) {
    state* s = malloc(sizeof(state));

    *s = (state){
        .dirs        = input,
        .curr        = {0, 0},
        .visited     = malloc(sizeof(pos)),
        .visited_len = 1,
    };
    s->visited[0] = s->curr;
    return s;
}

bool pos_equal(pos a, pos b) {
    return (bool)(a.x == b.x && a.y == b.y);
}
