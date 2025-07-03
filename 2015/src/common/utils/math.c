#include "utils.h"

#include <limits.h>
#include <stdarg.h>

int min(int count, ...) {
    va_list args;
    va_start(args, count);

    int min = INT_MAX;
    for (int i = 0; i < count; ++i) {
        int val = va_arg(args, int);
        if (val < min) {
            min = val;
        }
    }
    va_end(args);
    return min;
}

int max(int count, ...) {
    va_list args;
    va_start(args, count);

    int max = INT_MIN;
    for (int i = 0; i < count; ++i) {
        int val = va_arg(args, int);
        if (val > max) {
            max = val;
        }
    }
    va_end(args);
    return max;
}
