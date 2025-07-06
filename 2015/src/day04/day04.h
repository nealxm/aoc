#pragma once

#include <stdint.h>

void     day04_main(void);
uint32_t day04_part1(char*);
uint32_t day04_part2(char*);

typedef bool (*zero_checker)(const unsigned char*);

bool     check_5_zeros(const unsigned char*);
bool     check_6_zeros(const unsigned char*);
uint32_t find_md5_suffix(char*, zero_checker);
