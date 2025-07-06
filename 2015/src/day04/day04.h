#pragma once

void day04_main(void);
int  day04_part1(char*);
int  day04_part2(char*);

typedef bool (*zero_checker)(const unsigned char*);

bool check_5_zeros(const unsigned char*);
bool check_6_zeros(const unsigned char*);
int  find_md5_suffix(char*, zero_checker);
