/**
 * Scythe Girl Character
 */

#ifndef __SCYTHE_GIRL_H__
#define __SCYTHE_GIRL_H__

// Punchbowl headers
#include "Character.h"
#include "Scythe.h"

const int sg_damage_atk_neutral = 4;
const int sg_stun_atk_neutral = 6;
const float sg_knockback_atk_neutral = .8;

const int sg_damage_atk_side = 7;
const int sg_stun_atk_side = 7;
const float sg_knockback_atk_side = 1.1;

const int sg_damage_atk_down = 9;
const int sg_stun_atk_down = 8;
const float sg_knockback_atk_down = 1.0;

const int sg_damage_atk_up = 11;
const int sg_stun_atk_up = 7;
const float sg_knockback_atk_up = 1.2;

const int sg_damage_air_neutral = 5;
const int sg_stun_air_neutral = 3;
const float sg_knockback_air_neutral = 1.1;

const int sg_damage_air_back = 8;
const int sg_stun_air_back = 8;
const float sg_knockback_air_back = 0.8;

const int sg_damage_air_down = 4;
const int sg_stun_air_down = 0;
const float sg_knockback_air_down = 1.0;

const int sg_damage_air_up = 8;
const int sg_stun_air_up = 12;
const float sg_knockback_air_up = 1.1;

const int sg_damage_recovery =16;
const int sg_stun_recovery = 20;
const float sg_knockback_recovery = .9;

const std::string char_scythe_girl_type = "char_scythe_girl";

class Scythe;

class ScytheGirlChar : public Character {
    private:
        Scythe *scythe;
    public:
        ScytheGirlChar();

        // Selects and sets the animation of this character depending on the character's state
        virtual int animationSelector();

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

#endif // __SCYTHE_GIRL_H__
