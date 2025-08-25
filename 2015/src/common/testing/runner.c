#include "testing_base.h"

#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "invalid number of args '%s'\n", argv[0]);
        return 1;
    }
    return eval_test(argv[1], argv[2]);
}
