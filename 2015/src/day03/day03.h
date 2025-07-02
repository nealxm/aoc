#pragma once

#include <stdint.h>

void day03_main(void);
int  day03_part1(const char*);
int  day03_part2(const char*);

typedef struct {
    int x, y;
} pos;

typedef struct {
    const char* dirs;
    pos         curr, curr_r;
    pos*        visited;
    int         visited_len;
    int         _; //padding
} state;

state* state_init(const char*);
void   state_free(state*);
int    pos_move(pos*, char);
bool   pos_equal(pos a, pos b);
int    visited_add(pos**, int*, pos*);
