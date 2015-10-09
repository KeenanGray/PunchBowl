/**
* Character Test
*/

#ifndef __BULLCHAR_H__
#define __BULLCHAR_H__

// Punchbowl headers
#include "Character.h"

const int bull_damage_atk_neutral = 6;
const int bull_stun_atk_neutral = 5;
const float bull_knockback_atk_neutral = .8;

const int bull_damage_atk_side = 13;
const int bull_stun_atk_side = 10;
const float bull_knockback_atk_side = 1.1;

const int bull_damage_atk_down = 10;
const int bull_stun_atk_down = 12;
const float bull_knockback_atk_down = 1.0;

const int bull_damage_atk_up = 20;
const int bull_stun_atk_up = 15;
const float bull_knockback_atk_up = 1.2;

const int bull_damage_air_neutral = 8;
const int bull_stun_air_neutral = 8;
const float bull_knockback_air_neutral = .8;

const int bull_damage_air_down = 13;
const int bull_stun_air_down = 20;
const float bull_knockback_air_down = 1.0;

const int bull_damage_air_up = 12;
const int bull_stun_air_up = 15;
const float bull_knockback_air_up = 1.1;

const int bull_damage_recovery = 1;
const int bull_stun_recovery = 1;
const float bull_knockback_recovery = .3;

const std::string char_bull_type = "char_bull";

class BullChar : public Character {
private:
    
public:
    BullChar();

    virtual int neutral_jab(int frame);
    virtual int side_strike(int frame);
    virtual int up_strike(int frame);
    virtual int down_strike(int frame);
    virtual int neutral_air(int frame);
    virtual int down_air(int frame);
    virtual int up_air(int frame);
    virtual int recovery_special(int frame);
};

#endif // __CHAR_TEST_H__
