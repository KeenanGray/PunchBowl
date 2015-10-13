/**
* Character Test
*/

#ifndef __ROBOT_CHAR_H__
#define __ROBOT_CHAR_H__

// Punchbowl headers
#include "Character.h"

const int robot_damage_atk_neutral = 10;
const int robot_stun_atk_neutral = 12;
const float robot_knockback_atk_neutral = .8;

const int robot_damage_atk_side = 14;
const int robot_stun_atk_side = 16;
const float robot_knockback_atk_side = 1.2;

const int robot_damage_atk_down = 4;
const int robot_stun_atk_down = 4;
const float robot_knockback_atk_down = .4;

const int robot_damage_atk_up = 28;
const int robot_stun_atk_up = 20;
const float robot_knockback_atk_up = 1.4;

const int robot_damage_air_neutral = 12;
const int robot_stun_air_neutral = 14;
const float robot_knockback_air_neutral = 1.0;

const int robot_damage_air_back = 14;
const int robot_stun_air_back = 12;
const float robot_knockback_air_back = 1.3;

const int robot_damage_air_down = 18;
const int robot_stun_air_down = 20;
const float robot_knockback_air_down = 0.8;

const int robot_damage_air_up = 12;
const int robot_stun_air_up = 10;
const float robot_knockback_air_up = 1.2;

const int robot_damage_recovery = 4;
const int robot_stun_recovery = 3;
const float robot_knockback_recovery = .3;

const std::string char_robot_type = "char_robot";

class RobotChar : public Character {
private:
public:
    RobotChar();

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

#endif // __ROBOT_CHAR_H__
