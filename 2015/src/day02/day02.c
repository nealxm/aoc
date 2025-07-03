#include "day02.h"

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void day02_main(void) {
    char** input = file_to_array("./src/day02/data/input.txt");
    printf("2015:d02p1 - %d\n", day02_part1(input));
    printf("2015:d02p2 - %d\n", day02_part2(input));
    free_array((void**)input);
}

int day02_part1(char** input) {
    int total = 0;
    for (char** i = input; *i != nullptr; i++) {
        int l, w, h;
        if (sscanf(*i, "%dx%dx%d", &l, &w, &h) != 3) {
            fprintf(stderr, "failed to parse line '%s'\n", *i);
            exit(1);
        }
        int s1  = l * w;
        int s2  = w * h;
        int s3  = h * l;
        total  += 2 * (s1 + s2 + s3) + min(3, s1, s2, s3);
    }
    return total;
}

int day02_part2(char** input) {
    int total = 0;
    for (char** i = input; *i != nullptr; i++) {
        int l, w, h;
        if (sscanf(*i, "%dx%dx%d", &l, &w, &h) != 3) {
            fprintf(stderr, "failed to parse line '%s'\n", *i);
            exit(1);
        }
        total += 2 * (l + w + h - max(3, l, w, h)) + (l * w * h);
    }
    return total;
}
