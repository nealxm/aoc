#pragma once

#include <stdint.h>

void day03_main(void);
int  day03_part1(const char*);
int  day03_part2(const char*);

typedef struct {
    int x, y;
} pos;

//int64 to get rid of additional padding
typedef struct {
    const char* dirs;
    pos         curr;
    pos*        visited;
    int64_t     visited_len;
} state;

state* parse_input(const char*);
bool   pos_equal(pos a, pos b);
