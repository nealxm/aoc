#pragma once

#include <stdint.h>

#define TE(f, n, p, e)                                                                                                 \
    &(test_entry) {                                                                                                    \
        f, n, p, e                                                                                                     \
    }
#define RE(l, t, r)                                                                                                    \
    &(registry_entry) {                                                                                                \
        l, t, r                                                                                                        \
    }

typedef enum {
    one,
    two,
} part;

typedef struct {
    const char* file;
    const char* name;
    part p;
    int64_t expected;
} test_entry;

typedef struct {
    const char* library_name;
    const test_entry** tests;
    int64_t (*test_run)(const test_entry*);
} registry_entry;

uint8_t eval_test(const char*, const char*);

const registry_entry* find_re(const char*);
const test_entry* find_te(const registry_entry*, const char*);

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
static const registry_entry* registry[] = {
    RE("day01", day01_tests, day01_test_run),
    RE("day02", day02_tests, day02_test_run),
    RE("day03", day03_tests, day03_test_run),
    RE("day04", day04_tests, day04_test_run),
    RE("day05", day05_tests, day05_test_run),
    RE("day06", day06_tests, day06_test_run),
    RE("day07", day07_tests, day07_test_run),
    nullptr
};
