#include "utils.h"

#include <stdlib.h>

void free_array(void** array) {
    if (!array) {
        return;
    }
    for (int i = 0; array[i] != nullptr; ++i) {
        free(array[i]);
    }
    free((void*)array);
}
