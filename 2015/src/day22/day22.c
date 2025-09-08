#include "day22.h"

#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void day22_main(void) {
    char** input = file_to_array("./src/day22/data/input.txt");
    printf("2015:d22p1 - %hu\n", day22_part1((const char* const*)input));
    printf("2015:d22p2 - %hu\n", day22_part2((const char* const*)input));
    free_array((void**)input);
}

typedef struct {
    uint8_t cost, dmg, heal, armr, mana, dur;
} spell;

typedef enum {
    s_missile,
    s_drain,
    s_shield,
    s_poison,
    s_recharge,
    s_cnt,
} spell_type;

static const spell spells[s_cnt] = {
    [s_missile] = {53, 4, 0, 0, 0, 0},
    [s_drain] = {73, 2, 2, 0, 0, 0},
    [s_shield] = {113, 0, 0, 7, 0, 6},
    [s_poison] = {173, 3, 0, 0, 0, 6},
    [s_recharge] = {229, 0, 0, 0, 101, 5},
};

typedef struct {
    uint8_t p_hp,
        b_hp, b_dmg,
        sh_dur, po_dur, re_dur;
    uint16_t p_mana, p_spent;
} state;

static void state_free(state* s) {
    free(s);
}

static state* state_init(const char* const* input) {
    state* s = malloc(sizeof(state));
    if (!s) {
        fprintf(stderr, "failed to allocate state\n");
        goto bad_exit;
    }
    *s = (state){
        .p_hp = 50,
        .p_mana = 500
    };

    for (const char* const* l = input; *l; ++l) {
        if (
            sscanf(*l, "Hit Points: %hhu", &(s->b_hp)) +
            sscanf(*l, "Damage: %hhu", &(s->b_dmg)) != 1
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

static void apply_effects(state* s) {
    if (s->sh_dur > 0) {
        --(s->sh_dur);
    }
    if (s->po_dur > 0) {
        s->b_hp = spells[s_poison].dmg > s->b_hp ? 0 : s->b_hp - spells[s_poison].dmg;
        --(s->po_dur);
    }
    if (s->re_dur > 0) {
        s->p_mana += spells[s_recharge].mana;
        --(s->re_dur);
    }
}

static uint16_t find_target_game(state* s, uint16_t* best, bool hard) {
    if (s->p_spent > *best) {
        return UINT16_MAX;
    }
    if (hard) {
        if (s->p_hp <= 1) {
            return UINT16_MAX;
        }
        --(s->p_hp);
    }

    apply_effects(s);
    if (s->b_hp == 0) {
        *best = s->p_spent > *best ? s->p_spent : *best;
        return s->p_spent;
    }
    uint16_t min = UINT16_MAX;

    for (spell_type i = 0; i < s_cnt; ++i) {
        if (
            spells[i].cost > s->p_mana || //can't afford spell
            ((spells[i].dur != 0) &&      //spell already active
             ((i == s_shield && s->sh_dur != 0) || (i == s_poison && s->po_dur != 0) || (i == s_recharge && s->re_dur != 0))) ||
            (i == s_recharge && s->p_mana > 500) ||
            (!hard && i == s_shield && s->p_hp > s->b_dmg)
        ) {
            continue;
        }
        state curr = *s;
        curr.p_mana = s->p_mana - spells[i].cost;
        curr.p_spent = s->p_spent + spells[i].cost;

        switch (i) {
        case s_missile:
        case s_drain:
            curr.b_hp = curr.b_hp > spells[i].dmg ? curr.b_hp - spells[i].dmg : 0;
            curr.p_hp += spells[i].heal;
            break;
        case s_shield:
            curr.sh_dur = spells[s_shield].dur;
            break;
        case s_poison:
            curr.po_dur = spells[s_poison].dur;
            break;
        case s_recharge:
            curr.re_dur = spells[s_recharge].dur;
            break;
        case s_cnt:
        default:
            fprintf(stderr, "invalid spell");
            exit(1);
        }
        if (curr.b_hp == 0) {
            min = min < curr.p_spent ? min : curr.p_spent;
            continue;
        }

        apply_effects(&curr);
        if (curr.b_hp == 0) {
            min = min < curr.p_spent ? min : curr.p_spent;
            continue;
        }

        int8_t b_dmg_adj = curr.sh_dur > 0 ? curr.b_dmg - spells[s_shield].armr : (int8_t)curr.b_dmg; //armor adjustment
        b_dmg_adj = b_dmg_adj < 1 ? 1 : b_dmg_adj;                                                    //must do at least 1 dmg
        curr.p_hp = b_dmg_adj < curr.p_hp ? (uint8_t)(curr.p_hp - b_dmg_adj) : 0;                     //hp min is 0
        if (curr.p_hp == 0) {
            continue;
        }
        uint16_t res = find_target_game(&curr, best, hard);
        min = min < res ? min : res;
    }
    return min;
}

uint16_t day22_part1(const char* const* input) {
    state* s = state_init(input);
    uint16_t best = UINT16_MAX;
    uint16_t out = find_target_game(s, &best, false);
    state_free(s);
    return out;
}

uint16_t day22_part2(const char* const* input) {
    state* s = state_init(input);
    uint16_t best = UINT16_MAX;
    uint16_t out = find_target_game(s, &best, true);
    state_free(s);
    return out;
}
