#pragma once

#include <stdint.h>

#define TE(f, n, p, e) \
    &(test_entry) {    \
        f, n, p, e     \
    }
#define RE(l, t, r)     \
    &(registry_entry) { \
        l, t, r         \
    }

typedef enum {
    one,
    two
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
