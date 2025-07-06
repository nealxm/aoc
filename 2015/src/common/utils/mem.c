#include "utils.h"

#include <stdint.h>
#include <stdlib.h>

void free_array(void** array) {
    if (!array) {
        return;
    }
    for (int64_t i = 0; array[i] != nullptr; ++i) {
        free(array[i]);
    }
    free((void*)array);
}
