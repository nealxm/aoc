#include "day23.h"

#include "utils.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day23_main(void) {
    char** input = file_to_array("./src/day23/data/input.txt");
    printf("2015:d23p1 - %u\n", day23_part1((const char* const*)input));
    printf("2015:d23p2 - %u\n", day23_part2((const char* const*)input));
    free_array((void**)input);
}

typedef enum {
    hlf,
    tpl,
    inc,
    jmp,
    jie,
    jio,
} instruction;

typedef struct {
    instruction op;
    uint32_t* reg;
    int8_t jmp;
} instr;

typedef struct {
    instr** instrs;
    uint8_t num_instr;
    uint32_t *a, *b;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    for (instr** i = s->instrs; *i; ++i) {
        free(*i);
    }
    free((void*)s->instrs);
    free(s->a);
    free(s->b);
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate state");
        goto bad_exit;
    }
    s->num_instr = 0;

    for (const char* const* l = input; *l; ++l) {
        ++s->num_instr;
    }
    s->instrs = (instr**)calloc(s->num_instr + 1, sizeof(instr*));

    if (!s->instrs) {
        fprintf(stderr, "failed to allocate instrs");
        goto bad_exit;
    }
    s->a = malloc(sizeof(uint16_t));
    s->b = malloc(sizeof(uint16_t));

    if (!s->a || !s->b) {
        fprintf(stderr, "failed to allocate registers");
        goto bad_exit;
    }
    *(s->a) = 0;
    *(s->b) = 0;

    for (const char* const* l = input; *l; ++l) {
        ptrdiff_t i = l - input;

        s->instrs[i] = malloc(sizeof(instr));
        if (!s->instrs[i]) {
            fprintf(stderr, "failed to allocate instr");
            goto bad_exit;
        }
        instruction op_tmp = 0;
        char reg_tmp = 0;
        int8_t jmp_tmp = 0;

        if (sscanf(*l, "hlf %c", &reg_tmp) == 1) {
            op_tmp = hlf;
        } else if (sscanf(*l, "tpl %c", &reg_tmp) == 1) {
            op_tmp = tpl;
        } else if (sscanf(*l, "inc %c", &reg_tmp) == 1) {
            op_tmp = inc;
        } else if (sscanf(*l, "jmp %hhd", &jmp_tmp) == 1) {
            op_tmp = jmp;
        } else if (sscanf(*l, "jie %c, %hhd", &reg_tmp, &jmp_tmp) == 2) {
            op_tmp = jie;
        } else if (sscanf(*l, "jio %c, %hhd", &reg_tmp, &jmp_tmp) == 2) {
            op_tmp = jio;
        } else {
            fprintf(stderr, "failed to parse instruction");
            goto bad_exit;
        }
        if (op_tmp != jmp) {
            assert(reg_tmp == 'a' || reg_tmp == 'b');
        }
        *(s->instrs[i]) = (instr){
            .op = op_tmp,
            .reg = reg_tmp == 'a' ? s->a : s->b,
            .jmp = jmp_tmp,
        };
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

static uint32_t run_prog(state* s) {
    instr** i = s->instrs;

    do {

        switch ((*i)->op) {
        case hlf:
            *((*i)->reg) /= 2;
            ++i;
            break;
        case tpl:
            *((*i)->reg) *= 3;
            ++i;
            break;
        case inc:
            ++(*((*i)->reg));
            ++i;
            break;
        case jmp:
            i += (*i)->jmp;
            break;
        case jie:
            if (*((*i)->reg) % 2 == 0) {
                i += (*i)->jmp;
            } else {
                ++i;
            }
            break;
        case jio:
            if (*((*i)->reg) == 1) {
                i += (*i)->jmp;
            } else {
                ++i;
            }
            break;
        default:
            fprintf(stderr, "invalid operation");
            goto bad_exit;
        }
    } while (*i && i >= s->instrs && i < s->instrs + s->num_instr);
bad_exit:
    uint32_t out = *(s->b);
    return out;
}

uint32_t day23_part1(const char* const* input) {
    state* s = state_init(input);
    uint32_t out = run_prog(s);
    state_free(s);
    return out;
}

uint32_t day23_part2(const char* const* input) {
    state* s = state_init(input);
    *(s->a) = 1;
    uint32_t out = run_prog(s);
    state_free(s);
    return out;
}
