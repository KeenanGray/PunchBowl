/**
* Octopus Character
*/

#ifndef __OCTOPUSCHAR_H__
#define __OCTOPUSCHAR_H__

// Punchbowl headers
#include "Character.h"

const int octopus_damage_atk_neutral = 8;
const int octopus_stun_atk_neutral = 5;
const float octopus_knockback_atk_neutral = .8;

const int octopus_damage_atk_side = 12;
const int octopus_stun_atk_side = 10;
const float octopus_knockback_atk_side = 1.1;

const int octopus_damage_atk_down = 14;
const int octopus_stun_atk_down = 12;
const float octopus_knockback_atk_down = 1.2;

const int octopus_damage_atk_up = 20;
const int octopus_stun_atk_up = 15;
const float octopus_knockback_atk_up = 1.2;

const int octopus_damage_air_neutral = 8;
const int octopus_stun_air_neutral = 8;
const float octopus_knockback_air_neutral = 1.0;

const int octopus_damage_air_back = 11;
const int octopus_stun_air_back = 12;
const float octopus_knockback_air_back = 1.0;

const int octopus_damage_air_down = 13;
const int octopus_stun_air_down = 20;
const float octopus_knockback_air_down = 0.9;

const int octopus_damage_air_up = 17;
const int octopus_stun_air_up = 15;
const float octopus_knockback_air_up = 1.3;

const int octopus_damage_recovery = 3;
const int octopus_stun_recovery = 0;
const float octopus_knockback_recovery = .5;

const std::string char_octopus_type = "char_octopus";

class OctopusChar : public Character {
private:

public:
    OctopusChar();

    virtual int neutral_jab(int frame);
    virtual int side_strike(int frame);
    virtual int up_strike(int frame);
    virtual int down_strike(int frame);
    virtual int neutral_air(int frame);
    virtual int back_air(int frame);
    virtual int down_air(int frame);
    virtual int up_air(int frame);
    virtual int recovery_special(int frame);
};

#endif // __OCTOPUSCHAR_H__
