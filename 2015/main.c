#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
#include "day13.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* day;
    void (*func)(void);
} day;

static day days[25] = {
    {"1", day01_main},
    {"2", day02_main},
    {"3", day03_main},
    {"4", day04_main},
    {"5", day05_main},
    {"6", day06_main},
    {"7", day07_main},
    {"8", day08_main},
    {"9", day09_main},
    {"10", day10_main},
    {"11", day11_main},
    {"12", day12_main},
    {"13", day13_main},
};

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "invalid arguements: must specify an aoc day to run (1-25)\n");
        return 1;
    }
    int d = atoi(argv[1]);

    if (d < 1 || d > 25) {
        fprintf(stderr, "invalid day: either not implemented or not 1-25\n");
        return 1;
    }
    days[d - 1].func();
    return 0;
}
