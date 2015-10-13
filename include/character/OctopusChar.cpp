/**
* octopus Character
*/

// Dragonfly Engine headers
// Managers
#include "LogManager.h"
#include "ResourceManager.h"

// Punchbowl headers
#include "OctopusChar.h"

OctopusChar::OctopusChar() {
    this->setType(char_octopus_type);

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    this->l_stand = resource_manager.getSprite("octopus-left-spr");
    this->r_stand = resource_manager.getSprite("octopus-right-spr");
    this->l_walk = resource_manager.getSprite("octopus-left-walk-spr");
    this->r_walk = resource_manager.getSprite("octopus-right-walk-spr");
    this->l_dash = resource_manager.getSprite("octopus-left-dash-spr");
    this->r_dash = resource_manager.getSprite("octopus-right-dash-spr");
    this->l_crouch = resource_manager.getSprite("octopus-left-crouch-spr");
    this->r_crouch = resource_manager.getSprite("octopus-right-crouch-spr");
    this->l_crawl = resource_manager.getSprite("octopus-left-crawl-spr");
    this->r_crawl = resource_manager.getSprite("octopus-right-crawl-spr");
    this->l_jump = resource_manager.getSprite("octopus-left-jump-spr");
    this->r_jump = resource_manager.getSprite("octopus-right-jump-spr");
    this->l_air = resource_manager.getSprite("octopus-left-air-spr");
    this->r_air = resource_manager.getSprite("octopus-right-air-spr");
    this->l_roll = resource_manager.getSprite("octopus-left-roll-spr");
    this->r_roll = resource_manager.getSprite("octopus-right-roll-spr");
    this->l_dodge = resource_manager.getSprite("octopus-left-dodge-spr");
    this->r_dodge = resource_manager.getSprite("octopus-right-dodge-spr");
    this->l_fall = resource_manager.getSprite("octopus-left-fall-spr");
    this->r_fall = resource_manager.getSprite("octopus-right-fall-spr");
    this->l_stun = resource_manager.getSprite("octopus-left-stunned-spr");
    this->r_stun = resource_manager.getSprite("octopus-right-stunned-spr");

    this->l_atk_neutral = resource_manager.getSprite("octopus-left-atk-neutral-spr");
    this->r_atk_neutral = resource_manager.getSprite("octopus-right-atk-neutral-spr");
    this->l_atk_side = resource_manager.getSprite("octopus-left-atk-side-spr");
    this->r_atk_side = resource_manager.getSprite("octopus-right-atk-side-spr");
    this->l_atk_up = resource_manager.getSprite("octopus-left-atk-up-spr");
    this->r_atk_up = resource_manager.getSprite("octopus-right-atk-up-spr");
    this->l_atk_down = resource_manager.getSprite("octopus-left-atk-down-spr");
    this->r_atk_down = resource_manager.getSprite("octopus-right-atk-down-spr");

    this->l_air_neutral = resource_manager.getSprite("octopus-left-air-neutral-spr");
    this->r_air_neutral = resource_manager.getSprite("octopus-right-air-neutral-spr");
    this->l_air_up = resource_manager.getSprite("octopus-left-air-up-spr");
    this->r_air_up = resource_manager.getSprite("octopus-right-air-up-spr");
    this->l_air_down = resource_manager.getSprite("octopus-left-air-down-spr");
    this->r_air_down = resource_manager.getSprite("octopus-right-air-down-spr");
    this->l_air_back = resource_manager.getSprite("octopus-left-air-back-spr");
    this->r_air_back = resource_manager.getSprite("octopus-right-air-back-spr");
    this->l_recovery = resource_manager.getSprite("octopus-left-recovery-spr");
    this->r_recovery = resource_manager.getSprite("octopus-right-recovery-spr");

    this->stand_s = 15;
    this->walk_s = 8;
    this->dash_s = 5;
    this->crouch_s = 0;
    this->crawl_s = 10;
    this->jump_s = 2;
    this->air_s = 0;
    this->roll_s = 4;
    this->dodge_s = 8;
    this->stun_s = 0;
    this->stun_s = 0;

    this->atk_neutral_s = 4;
    this->atk_side_s = 4;
    this->atk_up_s = 4;
    this->atk_down_s = 6;
    this->air_neutral_s = 4;
    this->air_up_s = 5;
    this->air_down_s = 15;
    this->air_back_s = 8;
    this->recovery_s = 6;

    this->walk_div = 150.0;
    this->dash_div = 75.0;

    this->setObjectColor(df::RED);

    this->setSprite(this->l_stand);
    this->setSpriteSlowdown(this->stand_s);

    //setName(new PlayerName("octopus", this));
}

int OctopusChar::neutral_jab(int frame) {
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
            temp_relative_pos.setX(5);
            temp_direction.setX(2);
        }
        else {
            temp_relative_pos.setX(-9);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            octopus_stun_atk_neutral,
            octopus_damage_atk_neutral,
            octopus_knockback_atk_neutral,
            temp_direction,
            5, 2
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int OctopusChar::side_strike(int frame) {
    if (frame == 0) {
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->setXVelocity(.2);
        }
        else {
            this->setXVelocity(-.2);
        }
        this->attack_type = SIDE_STRIKE;
        this->attack_frames = 24;
        this->cancel_frames = 20;
    }
    else if (frame == 12) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(4);
            temp_direction.setX(2);
        }
        else {
            temp_relative_pos.setX(-8);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            octopus_stun_atk_side,
            octopus_damage_atk_side,
            octopus_knockback_atk_side,
            temp_direction,
            5, 2
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int OctopusChar::up_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = UP_STRIKE;
        this->attack_frames = 16;
        this->cancel_frames = 12;
    }
    else if (frame == 12) {
        df::Position temp_relative_pos(0, -6);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(0);
            temp_direction.setX(1);
        }
        else {
            temp_relative_pos.setX(-3);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            octopus_stun_atk_up,
            octopus_damage_atk_up,
            octopus_knockback_atk_up,
            temp_direction,
            3, 5
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int OctopusChar::down_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = DOWN_STRIKE;
        this->attack_frames = 18;
        this->cancel_frames = 12;
    }
    else if (frame == 12) {
        df::Position temp_relative_pos1(0, 3);
        df::Position temp_direction1(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos1.setX(-9);
            temp_direction1.setX(-3);
        }
        else {
            temp_relative_pos1.setX(6);
            temp_direction1.setX(3);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos1,
            octopus_stun_atk_down,
            octopus_damage_atk_down,
            octopus_knockback_atk_down,
            temp_direction1,
            3
            ));
        df::Position temp_relative_pos2(0, 3);
        df::Position temp_direction2(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos2.setX(6);
            temp_direction2.setX(3);
        }
        else {
            temp_relative_pos2.setX(-9);
            temp_direction2.setX(-3);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos2,
            octopus_stun_atk_down,
            octopus_damage_atk_down,
            octopus_knockback_atk_down,
            temp_direction2,
            3
            ));
    }
    else if (frame == 6) {
        this->clearHitboxes();
    }
    return 0;
}

int OctopusChar::neutral_air(int frame) {
    if (frame == 0) {
        this->attack_type = NEUTRAL_AIR;
        this->attack_frames = 16;
        this->cancel_frames = 16;
    }
    else if (frame == 12) {
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
            octopus_stun_air_neutral,
            octopus_damage_air_neutral,
            0,
            temp_direction,
            4,
            2
            ));
    }
    else if (frame == 8) {
        this->clearHitboxes();
    }
    else if (frame == 4) {
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
            octopus_stun_air_neutral,
            octopus_damage_air_neutral,
            octopus_knockback_air_neutral,
            temp_direction,
            4,
            2
            ));
    }
    return 0;
}


int OctopusChar::back_air(int frame) {
    if (frame == 0) {
        this->attack_type = BACK_AIR;
        this->attack_frames = 16;
        this->cancel_frames = 8;
    }
    else if (frame == 8) {
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
            octopus_stun_air_back,
            octopus_damage_air_back,
            octopus_knockback_air_back,
            temp_direction,
            3
            ));
    }
    else if (frame == 1) {
        this->clearHitboxes();
    }
    return 0;
}

int OctopusChar::down_air(int frame) {
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
            octopus_stun_air_down,
            octopus_damage_air_down,
            octopus_knockback_air_down,
            temp_direction,
            3
            ));
    }
    else if (frame == 7) {
        this->clearHitboxes();
    }
    return 0;
}

int OctopusChar::up_air(int frame) {
    if (frame == 0) {
        this->attack_type = UP_AIR;
        this->attack_frames = 15;
        this->cancel_frames = 15;
    }
    else if (frame == 8) {
        df::Position temp_relative_pos(0, -5);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(-2);
            temp_direction.setX(1);
        }
        else {
            temp_relative_pos.setX(-2);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            octopus_stun_air_up,
            octopus_damage_air_up,
            octopus_knockback_air_up,
            temp_direction,
            4, 3
            ));
    }
    return 0;
}

int OctopusChar::recovery_special(int frame) {
    if (frame == 0) {
        this->attack_type = RECOVERY_SPECIAL;
        this->attack_frames = 40;
        this->cancel_frames = 40;
        this->setYVelocity(-1.6);
        this->is_falling = true;
        df::Sound *p_sound = df::ResourceManager::getInstance().getSound("jump5");
        p_sound->play();
    }
    else if (frame % 12 == 11) {
        this->clearHitboxes();
        df::Position temp_relative_pos(-7, -4);
        df::Position temp_direction(0, -1);
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            octopus_stun_recovery,
            octopus_damage_recovery,
            octopus_knockback_recovery,
            temp_direction,
            15
            ));
    }
    return 0;
}
