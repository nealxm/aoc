#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char* file_to_string(const char* file) {
    FILE* f = fopen(file, "r");
    if (!f) {
        fprintf(stderr, "could not open '%s'\n", file);
        return nullptr;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "could not find end of '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    long file_size = ftell(f);
    if (file_size < 0) {
        fprintf(stderr, "could not determine size of '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    size_t f_size = (size_t)file_size;
    if (fseek(f, 0, SEEK_SET) != 0) {
        fprintf(stderr, "could not reset position of '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    char* string = malloc(f_size+1);
    if (!string) {
        fprintf(stderr, "could not allocate memory for '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    size_t elements = fread(string, 1, f_size, f);
    string[elements] = '\0';
    fclose(f);
    return string;
}
