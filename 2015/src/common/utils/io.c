#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const long file_size = ftell(f);
    if (file_size < 0) {
        fprintf(stderr, "could not determine size of '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    const size_t f_size = (size_t)file_size;
    if (fseek(f, 0, SEEK_SET) != 0) {
        fprintf(stderr, "could not reset position of '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    char* const string = malloc(f_size + 1);
    if (!string) {
        fprintf(stderr, "could not allocate memory for '%s'\n", file);
        fclose(f);
        return nullptr;
    }
    const size_t elements = fread(string, 1, f_size, f);
    string[elements] = '\0';
    fclose(f);
    return string;
}

char** file_to_array(const char* file) {
    FILE* f = fopen(file, "r");
    if (!f) {
        fprintf(stderr, "could not open '%s'\n", file);
        return nullptr;
    }
    char** lines = nullptr;
    size_t lines_len = 0;
    char* line = nullptr;
    size_t line_len = 0;

    while (getline(&line, &line_len, f) != -1) {
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        char** lines_new = (char**)realloc((void*)lines, sizeof(char*) * (lines_len + 2));
        if (!lines_new) {
            fprintf(stderr, "could not reallocate memory for next line '%s'\n", line);
            free(line);
            free_array((void**)lines);
            return nullptr;
        }
        lines = lines_new;

        char* const newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }
        lines[lines_len] = strdup(line);
        lines[++lines_len] = nullptr;
    }
    free(line);
    fclose(f);
    return lines;
}
