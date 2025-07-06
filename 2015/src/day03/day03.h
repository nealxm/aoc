#pragma once

#include <stdint.h>

void     day03_main(void);
uint16_t day03_part1(const char*);
uint16_t day03_part2(const char*);

typedef struct {
    int8_t x, y;
} pos;

typedef struct {
    const char* dirs;
    pos         curr, curr_r;
    int32_t     _1;
    pos*        visited;
    uint16_t    visited_len;
    int8_t      _2[6];
} state;

state*  state_init(const char*);
void    state_free(state*);
uint8_t pos_move(pos*, char);
bool    pos_equal(const pos*, const pos*);
uint8_t visited_add(pos**, uint16_t*, const pos*);
