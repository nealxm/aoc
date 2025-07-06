#include "utils.h"

#include <limits.h>
#include <stdarg.h>
#include <stdint.h>

int64_t min(uint8_t count, ...) {
    va_list args;
    va_start(args, count);

    int64_t min = INT64_MAX;
    for (uint8_t i = 0; i < count; ++i) {
        int64_t val = va_arg(args, int64_t);
        if (val < min) {
            min = val;
        }
    }
    va_end(args);
    return min;
}

int64_t max(uint8_t count, ...) {
    va_list args;
    va_start(args, count);

    int64_t max = INT64_MIN;
    for (uint8_t i = 0; i < count; ++i) {
        int64_t val = va_arg(args, int64_t);
        if (val > max) {
            max = val;
        }
    }
    va_end(args);
    return max;
}
