#include "day07.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void day07_main(void) {
    char** input = file_to_array("./src/day07/data/input.txt");
    printf("2015:d07p1 - %u\n", day07_part1(input));
    printf("2015:d07p2 - %u\n", day07_part2(input));
    free_array((void**)input);
}

typedef enum {
    assign,
    and,
    or,
    lshift,
    rshift,
    not
} op_kind;

typedef struct {
    op_kind kind;
    char *in1, *in2, *out;
    uint16_t arg;
} instr;

typedef struct {
    char* name;
    uint16_t val;
} wire;

typedef struct {
    instr** instrs;
    wire** wires;
} state;

static void state_free(state* s) {
    if (s->instrs) {
        for (instr** i = s->instrs; *i; ++i) {
            instr* inst = *i;

            free(inst->in1);
            free(inst->in2);
            free(inst->out);
            free(inst);
        }
        free((void*)s->instrs);
    }
    if (s->wires) {
        for (wire** w = s->wires; *w; ++w) {
            wire* wire_obj = *w;

            free(wire_obj->name);
            free(wire_obj);
        }
        free((void*)s->wires);
    }
    free(s);
}

static state* state_init(char** input) {
    state* s = malloc(sizeof(state));
    uint16_t lines = 0;
    for (char** l = input; *l; ++l) {
        ++lines;
    }
    instr** instrs = (instr**)calloc(lines + 1, sizeof(instr*));

    for (uint16_t i = 0; i < lines; ++i) {
        char* l = input[i];
        instr* new = calloc(1, sizeof(instr));
        char i1[4], i2[4], o[4];
        uint16_t a;

        if (sscanf(l, "%hu -> %s", &a, o) == 2) {
            new->kind = assign;
            new->arg = a;
            new->out = strdup(o);
        } else if (sscanf(l, "%s -> %s", i1, o) == 2) {
            new->kind = assign;
            new->in1 = strdup(i1);
            new->out = strdup(o);
        } else if (sscanf(l, "%hu AND %s -> %s", &a, i2, o) == 3) {
            new->kind = and;
            new->arg = a;
            new->in2 = strdup(i2);
            new->out = strdup(o);
        } else if (sscanf(l, "%s AND %s -> %s", i1, i2, o) == 3) {
            new->kind = and;
            new->in1 = strdup(i1);
            new->in2 = strdup(i2);
            new->out = strdup(o);
        } else if (sscanf(l, "%s OR %s -> %s", i1, i2, o) == 3) {
            new->kind = or ;
            new->in1 = strdup(i1);
            new->in2 = strdup(i2);
            new->out = strdup(o);
        } else if (sscanf(l, "%s LSHIFT %hu -> %s", i1, &a, o) == 3) {
            new->kind = lshift;
            new->in1 = strdup(i1);
            new->out = strdup(o);
            new->arg = a;
        } else if (sscanf(l, "%s RSHIFT %hu -> %s", i1, &a, o) == 3) {
            new->kind = rshift;
            new->in1 = strdup(i1);
            new->out = strdup(o);
            new->arg = a;
        } else if (sscanf(l, "NOT %s -> %s", i1, o) == 2) {
            new->kind = not;
            new->in1 = strdup(i1);
            new->out = strdup(o);
        } else {
            fprintf(stderr, "invalid instruction %s\n", l);
            free((void*)instrs);
            free(new);
            return nullptr;
        }
        instrs[i] = new;
    }
    s->instrs = instrs;
    s->wires = (wire**)calloc(1, sizeof(wire*));
    return s;
}

static uint16_t resolve_wire(state* s, char* n) {
    for (wire** w = s->wires; *w; ++w) {
        if (strcmp((*w)->name, n) == 0) {
            return (*w)->val;
        }
    }
    instr* curr = nullptr;

    for (instr** i = s->instrs; *i; ++i) {
        if (strcmp((*i)->out, n) == 0) {
            curr = *i;
            break;
        }
    }
    if (curr == nullptr) {
        fprintf(stderr, "wire %s not found in instructions\n", n);
        state_free(s);
        exit(1);
    }
    uint16_t res;

    switch (curr->kind) {
    case assign:
        if (!curr->in1) {
            res = curr->arg;
        } else {
            res = resolve_wire(s, curr->in1);
        }
        break;
    case and:
        if (!curr->in1) {
            res = curr->arg & resolve_wire(s, curr->in2);
        } else {
            res = resolve_wire(s, curr->in1) & resolve_wire(s, curr->in2);
        }
        break;
    case or:
        res = resolve_wire(s, curr->in1) | resolve_wire(s, curr->in2);
        break;
    case lshift:
        res = (uint16_t)(resolve_wire(s, curr->in1) << curr->arg);
        break;
    case rshift:
        res = resolve_wire(s, curr->in1) >> curr->arg;
        break;
    case not:
        res = ~resolve_wire(s, curr->in1);
        break;
    default:
        fprintf(stderr, "unknown instruction kind %u\n", curr->kind);
        state_free(s);
        exit(1);
    }
    wire* new = malloc(sizeof(wire));
    if (!new) {
        fprintf(stderr, "failed to allocate memory for new wire\n");
        state_free(s);
        exit(1);
    }
    new->name = strdup(n);
    new->val = res;

    uint16_t count = 0;
    for (wire** w = s->wires; *w; ++w) {
        ++count;
    }
    wire** tmp = (wire**)realloc((void*)s->wires, (count + 2) * sizeof(wire*));

    if (!tmp) {
        fprintf(stderr, "failed to reallocate memory for wires\n");
        free(new->name);
        free(new);
        state_free(s);
        exit(1);
    }
    s->wires = tmp;
    s->wires[count] = new;
    s->wires[count + 1] = nullptr;
    return res;
}

uint16_t day07_part1(char** input) {
    state* s = state_init(input);
    uint16_t out = resolve_wire(s, "a");
    state_free(s);
    return out;
}

uint16_t day07_part2(char** input) {
    state* s = state_init(input);
    uint16_t a_val = resolve_wire(s, "a");
    state_free(s);
    s = state_init(input);
    wire** tmp = (wire**)realloc((void*)s->wires, 2 * sizeof(wire*));

    if (!tmp) {
        fprintf(stderr, "failed to reallocate memory for wires\n");
        state_free(s);
        exit(1);
    }
    s->wires[0] = malloc(sizeof(wire));
    s->wires[0]->name = strdup("b");
    s->wires[0]->val = a_val;
    s->wires[1] = nullptr;
    uint16_t out = resolve_wire(s, "a");
    state_free(s);

    return out;
}
