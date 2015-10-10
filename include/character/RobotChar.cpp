/**
* Character Test
*/

// Dragonfly Engine headers
// Events
#include "EventOut.h"
// Managers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "RobotChar.h"

RobotChar::RobotChar() {
    this->setType(char_robot_type);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    this->l_stand = resource_manager.getSprite("robot-left-spr");
    this->r_stand = resource_manager.getSprite("robot-right-spr");
    this->l_walk = resource_manager.getSprite("robot-left-walk-spr");
    this->r_walk = resource_manager.getSprite("robot-right-walk-spr");
    this->l_dash = resource_manager.getSprite("robot-left-dash-spr");
    this->r_dash = resource_manager.getSprite("robot-right-dash-spr");
    this->l_crouch = resource_manager.getSprite("robot-left-crouch-spr");
    this->r_crouch = resource_manager.getSprite("robot-right-crouch-spr");
    this->l_crawl = resource_manager.getSprite("robot-left-crawl-spr");
    this->r_crawl = resource_manager.getSprite("robot-right-crawl-spr");
    this->l_jump = resource_manager.getSprite("robot-left-jump-spr");
    this->r_jump = resource_manager.getSprite("robot-right-jump-spr");
    this->l_air = resource_manager.getSprite("robot-left-air-spr");
    this->r_air = resource_manager.getSprite("robot-right-air-spr");
    this->l_roll = resource_manager.getSprite("robot-left-roll-spr");
    this->r_roll = resource_manager.getSprite("robot-right-roll-spr");
    this->l_dodge = resource_manager.getSprite("robot-left-dodge-spr");
    this->r_dodge = resource_manager.getSprite("robot-right-dodge-spr");
    this->l_fall = resource_manager.getSprite("robot-left-fall-spr");
    this->r_fall = resource_manager.getSprite("robot-right-fall-spr");
    this->l_stun = resource_manager.getSprite("robot-left-stunned-spr");
    this->r_stun = resource_manager.getSprite("robot-right-stunned-spr");

    this->l_atk_neutral = resource_manager.getSprite("robot-left-atk-neutral-spr");
    this->r_atk_neutral = resource_manager.getSprite("robot-right-atk-neutral-spr");
    this->l_atk_side = resource_manager.getSprite("robot-left-atk-side-spr");
    this->r_atk_side = resource_manager.getSprite("robot-right-atk-side-spr");
    this->l_atk_up = resource_manager.getSprite("robot-left-atk-up-spr");
    this->r_atk_up = resource_manager.getSprite("robot-right-atk-up-spr");
    this->l_atk_down = resource_manager.getSprite("robot-left-atk-down-spr");
    this->r_atk_down = resource_manager.getSprite("robot-right-atk-down-spr");
    this->l_air_neutral = resource_manager.getSprite("robot-left-air-neutral-spr");
    this->r_air_neutral = resource_manager.getSprite("robot-right-air-neutral-spr");
    this->l_air_up = resource_manager.getSprite("robot-left-air-up-spr");
    this->r_air_up = resource_manager.getSprite("robot-right-air-up-spr");
    this->l_air_down = resource_manager.getSprite("robot-left-air-down-spr");
    this->r_air_down = resource_manager.getSprite("robot-right-air-down-spr");
    this->l_air_back = resource_manager.getSprite("robot-left-air-back-spr");
    this->r_air_back = resource_manager.getSprite("robot-right-air-back-spr");
    this->l_recovery = resource_manager.getSprite("robot-left-recovery-spr");
    this->r_recovery = resource_manager.getSprite("robot-right-recovery-spr");


    this->stand_s = 15;
    this->walk_s = 8;
    this->dash_s = 6;
    this->crouch_s = 0;
    this->crawl_s = 10;
    this->jump_s = 2;
    this->air_s = 0;
    this->roll_s = 4;
    this->dodge_s = 8;
    this->stun_s = 0;
    this->stun_s = 0;

    this->atk_neutral_s = 4;
    this->atk_side_s = 5;
    this->atk_up_s = 5;
    this->atk_down_s = 8;
    this->recovery_s = 6;

    this->setObjectColor(df::RED);

    this->setSprite(this->l_stand);
    this->setSpriteSlowdown(this->stand_s);

    //setName(new PlayerName("Robot", this));
}

int RobotChar::neutral_jab(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = NEUTRAL_JAB;
        this->attack_frames = 16;
        this->cancel_frames = 12;
    }
    else if (frame == 12) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(8);
            temp_direction.setX(2);
        }
        else {
            temp_relative_pos.setX(-8);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_atk_neutral,
            robot_damage_atk_neutral,
            robot_knockback_atk_neutral,
            temp_direction
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int RobotChar::side_strike(int frame) {
    if (frame == 0) {
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->setXVelocity(.2);
        }
        else {
            this->setXVelocity(-.2);
        }
        this->attack_type = SIDE_STRIKE;
        this->attack_frames = 30;
        this->cancel_frames = 25;
    }
    else if (frame == 15) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(7);
            temp_direction.setX(2);
        }
        else {
            temp_relative_pos.setX(-7);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_atk_side,
            robot_damage_atk_side,
            robot_knockback_atk_side,
            temp_direction
            ));
    }
    else if (frame == 10) {
        this->clearHitboxes();
    }
    return 0;
}

int RobotChar::up_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = UP_STRIKE;
        this->attack_frames = 20;
        this->cancel_frames = 15;
    }
    else if (frame == 10) {
        df::Position temp_relative_pos(0, -3);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(1);
            temp_direction.setX(1);
        }
        else {
            temp_relative_pos.setX(-1);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_atk_up,
            robot_damage_atk_up,
            robot_knockback_atk_up,
            temp_direction
            ));
    }
    else if (frame == 15) {
        this->clearHitboxes();
    }
    return 0;
}


int RobotChar::down_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = DOWN_STRIKE;
        this->attack_frames = 24;
        this->cancel_frames = 16;
    }
    else if (frame == 12) {
        df::Position temp_relative_pos1(0, 3);
        df::Position temp_direction1(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos1.setX(-8);
            temp_direction1.setX(-3);
        }
        else {
            temp_relative_pos1.setX(8);
            temp_direction1.setX(3);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos1,
            robot_stun_atk_down,
            robot_damage_atk_down,
            robot_knockback_atk_down,
            temp_direction1
            ));
        df::Position temp_relative_pos2(0, 3);
        df::Position temp_direction2(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos2.setX(8);
            temp_direction2.setX(3);
        }
        else {
            temp_relative_pos2.setX(-8);
            temp_direction2.setX(-3);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos2,
            robot_stun_atk_down,
            robot_damage_atk_down,
            robot_knockback_atk_down,
            temp_direction2
            ));
    }
    else if (frame == 6) {
        this->clearHitboxes();
    }
    return 0;
}

int RobotChar::neutral_air(int frame) {
    if (frame == 0) {
        this->attack_type = NEUTRAL_AIR;
        this->attack_frames = 24;
        this->cancel_frames = 24;
    }
    else if (frame == 18) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(5);
            temp_direction.setX(2);
        }
        else {
            temp_relative_pos.setX(-7);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_air_neutral,
            robot_damage_air_neutral,
            0,
            temp_direction,
            4,
            2
            ));
    }
    else if (frame == 12) {
        this->clearHitboxes();
    }
    else if (frame == 6) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(4);
            temp_direction.setX(2);
        }
        else {
            temp_relative_pos.setX(-7);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_air_neutral,
            robot_damage_air_neutral,
            robot_knockback_air_neutral,
            temp_direction,
            4,
            2
            ));
    }
    return 0;
}


int RobotChar::back_air(int frame) {
    if (frame == 0) {
        this->attack_type = BACK_AIR;
        this->attack_frames = 20;
        this->cancel_frames = 11;
    }
    else if (frame == 10) {
        df::Position temp_relative_pos(0, 1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(-8);
            temp_direction.setX(-2);
        }
        else {
            temp_relative_pos.setX(5);
            temp_direction.setX(2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_air_back,
            robot_damage_air_back,
            robot_knockback_air_back,
            temp_direction,
            3
            ));
    }
    else if (frame == 1) {
        this->clearHitboxes();
    }
    return 0;
}

int RobotChar::down_air(int frame) {
    if (frame == 0) {
        this->attack_type = DOWN_AIR;
        this->attack_frames = 30;
        this->cancel_frames = 24;
    }
    else if (frame == 15) {
        df::Position temp_relative_pos(0, 5);
        df::Position temp_direction(0, 1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(-1);
        }
        else {
            temp_relative_pos.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_air_down,
            robot_damage_air_down,
            robot_knockback_air_down,
            temp_direction,
            3
            ));
    }
    else if (frame == 7) {
        this->clearHitboxes();
    }
    return 0;
}

int RobotChar::up_air(int frame) {
    if (frame == 0) {
        this->attack_type = UP_AIR;
        this->attack_frames = 21;
        this->cancel_frames = 21;
    }
    else if (frame == 7) {
        df::Position temp_relative_pos(0, -5);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(-1);
            temp_direction.setX(1);
        }
        else {
            temp_relative_pos.setX(-2);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_air_up,
            robot_damage_air_up,
            robot_knockback_air_up,
            temp_direction,
            3, 2
            ));
    }
    return 0;
}


int RobotChar::recovery_special(int frame) {
    if (frame == 0) {
        this->attack_type = RECOVERY_SPECIAL;
        this->attack_frames = 40;
        this->cancel_frames = 0;
        this->setYVelocity(-1.6);
        this->is_falling = true;
    }
    else if (frame % 12 == 11) {
        this->clearHitboxes();
        df::Position temp_relative_pos(-9, -4);
        df::Position temp_direction(0, -1);
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            robot_stun_recovery,
            robot_damage_recovery,
            robot_knockback_recovery,
            temp_direction,
            19
            ));
    }
    return 0;
}
