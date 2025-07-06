#pragma once

#include <stdint.h>

char* file_to_string(const char*);

void   free_array(void**);
char** file_to_array(const char*);

int64_t min(uint8_t, ...);
int64_t max(uint8_t, ...);
