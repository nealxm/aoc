#include "testing.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t eval_test(const char* re_name, const char* te_name) {
    const registry_entry* re_curr = find_re(re_name);
    const test_entry*     te_curr = find_te(re_curr, te_name);

    int64_t r = re_curr->test_run(te_curr);
    if (r != te_curr->expected) {
        fprintf(stderr, "'%s' failed: expected %lld, got %lld\n", te_name, te_curr->expected, r);
        return 1;
    }
    return 0;
}

const registry_entry* find_re(const char* re_name) {
    const registry_entry* re_curr = nullptr;

    for (const registry_entry* const* re = registry; *re != nullptr; ++re) {
        if (strcmp(re_name, (*re)->library_name) == 0) {
            re_curr = *re;
            break;
        }
    }
    if (!re_curr) {
        fprintf(stderr, "failed to find registry entry '%s'\n", re_name);
        exit(1);
    }
    return re_curr;
}

const test_entry* find_te(const registry_entry* re_curr, const char* te_name) {
    const test_entry* te_curr = nullptr;

    for (const test_entry* const* te = re_curr->tests; *te != nullptr; ++te) {
        if (strcmp(te_name, (*te)->name) == 0) {
            te_curr = *te;
            break;
        }
    }
    if (!te_curr) {
        fprintf(stderr, "failed to find test entry '%s'\n", te_name);
        exit(1);
    }
    return te_curr;
}
