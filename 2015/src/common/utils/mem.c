#include "utils.h"

#include <stdlib.h>

void free_array(void** array) {
    if (!array) {
        return;
    }
    for (void** i = array; *i; ++i) {
        free(*i);
    }
    free((void*)array);
}
