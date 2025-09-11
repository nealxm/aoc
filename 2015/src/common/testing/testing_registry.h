#include "testing_base.h"

#include <stdint.h>

extern const test_entry* day01_tests[];
int64_t day01_test_run(const test_entry*);
extern const test_entry* day02_tests[];
int64_t day02_test_run(const test_entry*);
extern const test_entry* day03_tests[];
int64_t day03_test_run(const test_entry*);
extern const test_entry* day04_tests[];
int64_t day04_test_run(const test_entry*);
extern const test_entry* day05_tests[];
int64_t day05_test_run(const test_entry*);
extern const test_entry* day06_tests[];
int64_t day06_test_run(const test_entry*);
extern const test_entry* day07_tests[];
int64_t day07_test_run(const test_entry*);
extern const test_entry* day08_tests[];
int64_t day08_test_run(const test_entry*);
extern const test_entry* day09_tests[];
int64_t day09_test_run(const test_entry*);
extern const test_entry* day10_tests[];
int64_t day10_test_run(const test_entry*);
extern const test_entry* day11_tests[];
int64_t day11_test_run(const test_entry*);
extern const test_entry* day12_tests[];
int64_t day12_test_run(const test_entry*);
extern const test_entry* day13_tests[];
int64_t day13_test_run(const test_entry*);
extern const test_entry* day14_tests[];
int64_t day14_test_run(const test_entry*);
extern const test_entry* day15_tests[];
int64_t day15_test_run(const test_entry*);
extern const test_entry* day16_tests[];
int64_t day16_test_run(const test_entry*);
extern const test_entry* day17_tests[];
int64_t day17_test_run(const test_entry*);
extern const test_entry* day18_tests[];
int64_t day18_test_run(const test_entry*);
extern const test_entry* day19_tests[];
int64_t day19_test_run(const test_entry*);
extern const test_entry* day20_tests[];
int64_t day20_test_run(const test_entry*);
extern const test_entry* day21_tests[];
int64_t day21_test_run(const test_entry*);
extern const test_entry* day22_tests[];
int64_t day22_test_run(const test_entry*);
extern const test_entry* day23_tests[];
int64_t day23_test_run(const test_entry*);
extern const test_entry* day24_tests[];
int64_t day24_test_run(const test_entry*);

static const registry_entry* registry[] = {
    RE("day01", day01_tests, day01_test_run),
    RE("day02", day02_tests, day02_test_run),
    RE("day03", day03_tests, day03_test_run),
    RE("day04", day04_tests, day04_test_run),
    RE("day05", day05_tests, day05_test_run),
    RE("day06", day06_tests, day06_test_run),
    RE("day07", day07_tests, day07_test_run),
    RE("day08", day08_tests, day08_test_run),
    RE("day09", day09_tests, day09_test_run),
    RE("day10", day10_tests, day10_test_run),
    RE("day11", day11_tests, day11_test_run),
    RE("day12", day12_tests, day12_test_run),
    RE("day13", day13_tests, day13_test_run),
    RE("day14", day14_tests, day14_test_run),
    RE("day15", day15_tests, day15_test_run),
    RE("day16", day16_tests, day16_test_run),
    RE("day17", day17_tests, day17_test_run),
    RE("day18", day18_tests, day18_test_run),
    RE("day19", day19_tests, day19_test_run),
    RE("day20", day20_tests, day20_test_run),
    RE("day21", day21_tests, day21_test_run),
    RE("day22", day22_tests, day22_test_run),
    RE("day23", day23_tests, day23_test_run),
    RE("day24", day24_tests, day24_test_run),
    nullptr
};
