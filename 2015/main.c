#include "day01.h"
#include "day02.h"
#include "day03.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* day;
    void        (*func)(void);
} day;

static day days[25] = {
    {"1", day01_main},
    {"2", day02_main},
    {"3", day03_main},
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "invalid arguements: must specify an aoc day to run (1-25)\n");
        return 1;
    }
    int d = atoi(argv[1]);

    if (d < 1 || d > 25) {
        fprintf(stderr, "invalid day: either not implemented or not 1-25\n");
    } else {
        days[d - 1].func();
    }
    return 0;
}
