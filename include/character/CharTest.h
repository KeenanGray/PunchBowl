/**
 * Character Test
 */

#ifndef __CHAR_TEST_H__
#define __CHAR_TEST_H__

// Punchbowl headers
#include "Character.h"

const int bull_damage_atk_neutral = 6;
const int bull_stun_atk_neutral = 5;
const float bull_knockback_atk_neutral = .9;

const int bull_damage_atk_side = 13;
const int bull_stun_atk_side = 10;
const float bull_knockback_atk_side = 1.4;

const int bull_damage_atk_down = 1;
const int bull_stun_atk_down = 1;
const float bull_knockback_atk_down = .3;

const int bull_damage_atk_up = 10;
const int bull_stun_atk_up = 10;
const float bull_knockback_atk_up = 1.0;

const int bull_damage_air_neutral = 1;
const int bull_stun_air_neutral = 1;
const float bull_knockback_air_neutral = .3;

const int bull_damage_air_down = 1;
const int bull_stun_air_down = 1;
const float bull_knockback_air_down = .3;

const int bull_damage_air_up = 1;
const int bull_stun_air_up = 1;
const float bull_knockback_air_up = .3;

const int bull_damage_recovery = 1;
const int bull_stun_recovery = 1;
const float bull_knockback_recovery = .3;

const std::string char_bull_type = "char_bull";

class CharTest : public Character {
    private:
        int out();
    public:
        CharTest();

        int eventHandler(const df::Event *p_e);

        virtual int neutral_jab(int frame);
        virtual int side_strike(int frame);
        virtual int up_strike(int frame);
};

#endif // __CHAR_TEST_H__
