#include "day21.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void day21_main(void) {
    char** input = file_to_array("./src/day21/data/input.txt");
    printf("2015:d21p1 - %hu\n", day21_part1((const char* const*)input));
    printf("2015:d21p2 - %hu\n", day21_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    uint8_t cost, dmg, armr;
} item;

typedef enum {
    w_dagger,
    w_ssword,
    w_warhammer,
    w_lsword,
    w_axe,
    w_cnt
} weapon_item;

typedef enum {
    a_none,
    a_leather,
    a_chain,
    a_splint,
    a_banded,
    a_plate,
    a_cnt
} armor_item;

typedef enum {
    r_none,
    r_dmg1,
    r_dmg2,
    r_dmg3,
    r_def1,
    r_def2,
    r_def3,
    r_cnt
} ring_item;

static const item weapons[w_cnt] = {
    {8, 4, 0},
    {10, 5, 0},
    {25, 6, 0},
    {40, 7, 0},
    {74, 8, 0}
};

static const item armors[a_cnt] = {
    {0, 0, 0},
    {13, 0, 1},
    {31, 0, 2},
    {53, 0, 3},
    {75, 0, 4},
    {102, 0, 5}
};

static const item rings[r_cnt] = {
    {25, 1, 0},
    {50, 2, 0},
    {100, 3, 0},
    {20, 0, 1},
    {40, 0, 2},
    {80, 0, 3}
};

typedef struct {
    uint8_t hp, dmg, armr;
} character;

typedef struct {
    character *plyr, *boss;
} state;

static void state_free(state* s) {
    if (!s) {
        return;
    }
    free(s->plyr);
    free(s->boss);
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate state\n");
        goto bad_exit;
    }
    *s = (state){
        .plyr = malloc(sizeof(character)),
        .boss = malloc(sizeof(character))
    };
    if (!s->plyr || !s->boss) {
        fprintf(stderr, "failed to allocate plyr or boss\n");
        goto bad_exit;
    }
    *(s->plyr) = (character){100, 0, 0};
    for (const char* const* l = input; *l; ++l) {
        if (
            sscanf(*l, "Hit Points: %hhu", &(s->boss->hp)) +
            sscanf(*l, "Damage: %hhu", &(s->boss->dmg)) +
            sscanf(*l, "Armor: %hhu", &(s->boss->armr)) != 1
        ) {
            fprintf(stderr, "failed to parse line\n");
            goto bad_exit;
        }
    }
    return s;
bad_exit:
    state_free(s);
    exit(1);
}

static bool sim_game(state* s, character* curr) {
    uint8_t p_dmg_adj = (curr->dmg > s->boss->armr) ? curr->dmg - s->boss->armr : 1;
    uint8_t b_dmg_adj = (s->boss->dmg > curr->armr) ? s->boss->dmg - curr->armr : 1;

    uint8_t p_win = (s->boss->hp + p_dmg_adj - 1) / p_dmg_adj;
    uint8_t b_win = (curr->hp + b_dmg_adj - 1) / b_dmg_adj;

    return p_win <= b_win;
}

uint16_t day21_part1(const char* const* input) {
    state* s = state_init(input);
    uint16_t min = UINT16_MAX;

    for (weapon_item w = 0; w < w_cnt; ++w) {
        for (armor_item a = 0; a < a_cnt; ++a) {
            for (ring_item r1 = 0; r1 < r_cnt; ++r1) {
                for (ring_item r2 = 0; r2 < r_cnt; ++r2) {

                    if (r1 == r2 && r1 != r_none) {
                        continue;
                    }
                    character curr = {
                        .hp = s->plyr->hp,
                        .dmg = weapons[w].dmg + rings[r1].dmg + rings[r2].dmg,
                        .armr = armors[a].armr + rings[r1].armr + rings[r2].armr
                    };

                    if (!sim_game(s, &curr)) {
                        continue;
                    }
                    uint16_t cost = weapons[w].cost + armors[a].cost + rings[r1].cost + rings[r2].cost;
                    min = cost < min ? cost : min;
                }
            }
        }
    }
    state_free(s);
    return min;
}

uint16_t day21_part2(const char* const* input) {
    state* s = state_init(input);
    uint16_t max = 0;

    for (weapon_item w = 0; w < w_cnt; ++w) {
        for (armor_item a = 0; a < a_cnt; ++a) {
            for (ring_item r1 = 0; r1 < r_cnt; ++r1) {
                for (ring_item r2 = 0; r2 < r_cnt; ++r2) {

                    if (r1 == r2 && r1 != r_none) {
                        continue;
                    }
                    character curr = {
                        .hp = s->plyr->hp,
                        .dmg = weapons[w].dmg + rings[r1].dmg + rings[r2].dmg,
                        .armr = armors[a].armr + rings[r1].armr + rings[r2].armr
                    };

                    if (sim_game(s, &curr)) {
                        continue;
                    }
                    uint16_t cost = weapons[w].cost + armors[a].cost + rings[r1].cost + rings[r2].cost;
                    max = cost > max ? cost : max;
                }
            }
        }
    }
    state_free(s);
    return max;
}
