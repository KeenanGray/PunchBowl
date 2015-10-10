/**
 * Character ScytheGirl
 */

// Dragonfly Engine headers
// Managers
#include "LogManager.h"
#include "ResourceManager.h"

// Punchbowl headers
#include "ScytheGirlChar.h"

ScytheGirlChar::ScytheGirlChar() {
    this->setType(char_scythe_girl_type);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    this->l_stand = resource_manager.getSprite("sg-left-spr");
    this->r_stand = resource_manager.getSprite("sg-right-spr");
    this->l_walk = resource_manager.getSprite("sg-left-walk-spr");
    this->r_walk = resource_manager.getSprite("sg-right-walk-spr");
    this->l_dash = resource_manager.getSprite("sg-left-dash-spr");
    this->r_dash = resource_manager.getSprite("sg-right-dash-spr");
    this->l_crouch = resource_manager.getSprite("sg-left-crouch-spr");
    this->r_crouch = resource_manager.getSprite("sg-right-crouch-spr");
    this->l_crawl = resource_manager.getSprite("sg-left-crawl-spr");
    this->r_crawl = resource_manager.getSprite("sg-right-crawl-spr");
    this->l_jump = resource_manager.getSprite("sg-left-jump-spr");
    this->r_jump = resource_manager.getSprite("sg-right-jump-spr");
    this->l_air = resource_manager.getSprite("sg-left-air-spr");
    this->r_air = resource_manager.getSprite("sg-right-air-spr");
    this->l_roll = resource_manager.getSprite("sg-left-roll-spr");
    this->r_roll = resource_manager.getSprite("sg-right-roll-spr");
    this->l_dodge = resource_manager.getSprite("sg-left-dodge-spr");
    this->r_dodge = resource_manager.getSprite("sg-right-dodge-spr");
    this->l_fall = resource_manager.getSprite("sg-left-fall-spr");
    this->r_fall = resource_manager.getSprite("sg-right-fall-spr");
    this->l_stun = resource_manager.getSprite("sg-left-stunned-spr");
    this->r_stun = resource_manager.getSprite("sg-right-stunned-spr");

    this->l_atk_neutral = resource_manager.getSprite("sg-left-atk-neutral-spr");
    this->r_atk_neutral = resource_manager.getSprite("sg-right-atk-neutral-spr");
    this->l_atk_side = resource_manager.getSprite("sg-left-atk-side-spr");
    this->r_atk_side = resource_manager.getSprite("sg-right-atk-side-spr");
    this->l_atk_up = resource_manager.getSprite("sg-left-atk-up-spr");
    this->r_atk_up = resource_manager.getSprite("sg-right-atk-up-spr");
    this->l_atk_down = resource_manager.getSprite("sg-left-atk-down-spr");
    this->r_atk_down = resource_manager.getSprite("sg-right-atk-down-spr");

    this->l_air_neutral = resource_manager.getSprite("sg-left-air-neutral-spr");
    this->r_air_neutral = resource_manager.getSprite("sg-right-air-neutral-spr");
    this->l_air_up = resource_manager.getSprite("sg-left-air-up-spr");
    this->r_air_up = resource_manager.getSprite("sg-right-air-up-spr");
    this->l_air_down = resource_manager.getSprite("sg-left-air-down-spr");
    this->r_air_down = resource_manager.getSprite("sg-right-air-down-spr");
    this->l_air_back = resource_manager.getSprite("sg-left-air-back-spr");
    this->r_air_back = resource_manager.getSprite("sg-right-air-back-spr");
    this->l_recovery = resource_manager.getSprite("sg-left-recovery-spr");
    this->r_recovery = resource_manager.getSprite("sg-right-recovery-spr");

    this->stand_s = 50;
    this->walk_s = 10;
    this->dash_s = 7;
    this->crouch_s = 0;
    this->crawl_s = 10;
    this->jump_s = 2;
    this->air_s = 5;
    this->roll_s = 6;
    this->dodge_s = 8;
    this->fall_s = 5;
    this->stun_s = 0;

    this->atk_neutral_s = 5;
    this->atk_side_s = 4;
    this->atk_up_s = 10;
    this->atk_down_s = 10;
    this->air_neutral_s = 6;
    this->air_up_s = 6;
    this->air_down_s = 6;
    this->air_back_s = 0;
    this->recovery_s = 5;

    this->terminal_velocity = 0.4;
    this->cancel_roll_frames = 14;
    this->roll_speed = 0.8;

    this->scythe = new Scythe(this);

    this->setObjectColor(df::RED);

    this->setSprite(this->l_stand);
    this->setSpriteSlowdown(this->stand_s);
    
    setName(new PlayerName("Scythe", this));
}

int ScytheGirlChar::animationSelector() {

    // Decrement animation frames
    if (this->stun_frames > 0) {
        this->stun_frames--;
    }
    if (this->attack_frames > 0) {
        this->attack_frames--;
    }
    if (this->cancel_frames > 0) {
        this->cancel_frames--; 
    }
    if (this->roll_frames > 0) {
        this->roll_frames--;
    }
    if (this->dodge_frames > 0) {
        this->dodge_frames--;
    }
    if (this->invincible_frames > 0) {
        this->invincible_frames--;
    }

    // Check if in attack animation
    if (this->attack_type != UNDEFINED_ATTACK) {
        if (this->attack_frames > 0) {
            // Select the proper attack animation
            if (this->getFacingDirection() == FACING_LEFT) {
                switch (this->attack_type) {
                    case NEUTRAL_JAB:
                        this->neutral_jab(this->attack_frames);
                        this->switchToSprite(this->l_atk_neutral, this->atk_neutral_s);
                        break;
                    case SIDE_STRIKE:
                        this->side_strike(this->attack_frames);
                        this->switchToSprite(this->l_atk_side, this->atk_side_s);
                        break;
                    case DOWN_STRIKE:
                        this->down_strike(this->attack_frames);
                        this->switchToSprite(this->l_atk_down, this->atk_down_s);
                        break;
                    case UP_STRIKE:
                        this->up_strike(this->attack_frames);
                        this->switchToSprite(this->l_atk_up, this->atk_up_s);
                        break;
                    case NEUTRAL_AIR:
                        this->neutral_air(this->attack_frames);
                        this->switchToSprite(this->l_air_neutral, this->air_neutral_s);
                        break;
                    case BACK_AIR:
                        this->back_air(this->attack_frames);
                        this->switchToSprite(this->l_air_back, this->air_back_s);
                        break;
                    case DOWN_AIR:
                        this->down_air(this->attack_frames);
                        this->switchToSprite(this->l_air_down, this->air_down_s);
                        break;
                    case UP_AIR:
                        this->up_air(this->attack_frames);
                        this->switchToSprite(this->l_air_up, this->air_up_s);
                        break;
                    case RECOVERY_SPECIAL:
                        this->recovery_special(this->attack_frames);
                        this->switchToSprite(this->l_recovery, this->recovery_s);
                        break;
                }
            } else {
                switch (this->attack_type) {
                    case NEUTRAL_JAB:
                        this->neutral_jab(this->attack_frames);
                        this->switchToSprite(this->r_atk_neutral, this->atk_neutral_s);
                        break;
                    case SIDE_STRIKE:
                        this->side_strike(this->attack_frames);
                        this->switchToSprite(this->r_atk_side, this->atk_side_s);
                        break;
                    case DOWN_STRIKE:
                        this->down_strike(this->attack_frames);
                        this->switchToSprite(this->r_atk_down, this->atk_down_s);
                        break;
                    case UP_STRIKE:
                        this->up_strike(this->attack_frames);
                        this->switchToSprite(this->r_atk_up, this->atk_up_s);
                        break;
                    case NEUTRAL_AIR:
                        this->neutral_air(this->attack_frames);
                        this->switchToSprite(this->r_air_neutral, this->air_neutral_s);
                        break;
                    case BACK_AIR:
                        this->back_air(this->attack_frames);
                        this->switchToSprite(this->r_air_back, this->air_back_s);
                        break;
                    case DOWN_AIR:
                        this->down_air(this->attack_frames);
                        this->switchToSprite(this->r_air_down, this->air_down_s);
                        break;
                    case UP_AIR:
                        this->up_air(this->attack_frames);
                        this->switchToSprite(this->r_air_up, this->air_up_s);
                        break;
                    case RECOVERY_SPECIAL:
                        this->recovery_special(this->attack_frames);
                        this->switchToSprite(this->r_recovery, this->recovery_s);
                        break;
                }
            }
            return 0;
        } else {
            // When the attack is over, reset the animation
            // And clear the hitboxes
            this->clearHitboxes();
            this->attack_type = UNDEFINED_ATTACK;
        }
        return 0;
    }
    if (this->stun_frames > 0) {
        // Select stun animation
        if (this->getFacingDirection() == FACING_LEFT) {
            this->scythe->switchOrientation(SCYTHE_0_CW);
            this->scythe->setRelativePos(df::Position(1, -2));
            this->switchToSprite(this->l_stun, this->stun_s);
        } else {
            this->scythe->switchOrientation(SCYTHE_0_CCW);
            this->scythe->setRelativePos(df::Position(0, -2));
            this->switchToSprite(this->r_stun, this->stun_s);
        }
        return 0;
    }
    if (this->currently_in_jump) {
        // Select jumping animation
        if (this->jump_frames < DEFAULT_LONGHOP_FRAMES) {
            if (this->getFacingDirection() == FACING_LEFT) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -3));
                this->switchToSprite(this->l_jump, this->jump_s);
            } else {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -3));
                this->switchToSprite(this->r_jump, this->jump_s);
            }
            return 0;
        }
    }
    if (this->on_ground) {
        // Select some ground animation
        if (this->getFacingDirection() == FACING_LEFT) {
            if (this->roll_frames > 0) {
                this->scythe->switchOrientation(SCYTHE_270_CW);
                this->scythe->setRelativePos(df::Position(0, 0));
                this->switchToSprite(this->l_roll, this->roll_s);
            } else if (this->dodge_frames > 0) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -3));
                this->switchToSprite(this->l_dodge, this->dodge_s);
            } else if (this->current_movement == STANDING) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -2));
                this->switchToSprite(this->l_stand, this->stand_s);
            } else if (this->current_movement == WALKING) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -2));
                this->switchToSprite(this->l_walk, this->walk_s);
            } else if (this->current_movement == DASHING) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(0, -2));
                this->switchToSprite(this->l_dash, this->dash_s);
            } else if (this->current_movement == CROUCHED) {
                this->scythe->switchOrientation(SCYTHE_270_CW);
                this->scythe->setRelativePos(df::Position(1, 0));
                this->switchToSprite(this->l_crouch, this->crouch_s);
            } else if (this->current_movement == CRAWLING) {
                this->scythe->switchOrientation(SCYTHE_270_CW);
                this->scythe->setRelativePos(df::Position(1, 0));
                this->switchToSprite(this->l_crawl, this->crawl_s);
            }
        } else {
            if (this->roll_frames > 0) {
                this->scythe->switchOrientation(SCYTHE_90_CCW);
                this->scythe->setRelativePos(df::Position(0, 0));
                this->switchToSprite(this->r_roll, this->roll_s);
            } else if (this->dodge_frames > 0) {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -3));
                this->switchToSprite(this->r_dodge, this->dodge_s);
            }else if (this->current_movement == STANDING) {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -2));
                this->switchToSprite(this->r_stand, this->stand_s);
            } else if (this->current_movement == WALKING) {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -2));
                this->switchToSprite(this->r_walk, this->walk_s);
            } else if (this->current_movement == DASHING) {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -2));
                this->switchToSprite(this->r_dash, this->dash_s);
            } else if (this->current_movement == CROUCHED) {
                this->scythe->switchOrientation(SCYTHE_90_CCW);
                this->scythe->setRelativePos(df::Position(0, 0));
                this->switchToSprite(this->r_crouch, this->crouch_s);
            } else if (this->current_movement == CRAWLING) {
                this->scythe->switchOrientation(SCYTHE_90_CCW);
                this->scythe->setRelativePos(df::Position(0, 0));
                this->switchToSprite(this->r_crawl, this->crawl_s);
            }
        }
        return 0;
    } else {
        if (this->getFacingDirection() == FACING_LEFT) {
            if (this->dodge_frames > 0) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -3));
                this->switchToSprite(this->l_dodge, this->dodge_s);
            } else if (this->is_falling) {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -5));
                this->switchToSprite(this->l_fall, this->fall_s);
            } else {
                this->scythe->switchOrientation(SCYTHE_0_CW);
                this->scythe->setRelativePos(df::Position(1, -4));
                this->switchToSprite(this->l_air, this->air_s);
            }
        } else {
            if (this->dodge_frames > 0) {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -3));
                this->switchToSprite(this->r_dodge, this->dodge_s);
            } else if (this->is_falling) {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -5));
                this->switchToSprite(this->r_fall, this->fall_s);
            } else {
                this->scythe->switchOrientation(SCYTHE_0_CCW);
                this->scythe->setRelativePos(df::Position(0, -4));
                this->switchToSprite(this->r_air, this->air_s);
            }
        }
        return 0;
    }
}

int ScytheGirlChar::neutral_jab(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = NEUTRAL_JAB;
        this->attack_frames = 15;
        this->cancel_frames = 10;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_90_CCW);
            this->scythe->setRelativePos(df::Position(3, -2));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_270_CW);
            this->scythe->setRelativePos(df::Position(-3, -2));
        }
    }
    else if (frame == 10) {
        df::Position temp_relative_pos(0, -4);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(4, -3));
            temp_relative_pos.setX(10);
            temp_direction.setX(3);
        }
        else {
            this->scythe->setRelativePos(df::Position(-4, -3));
            temp_relative_pos.setX(-12);
            temp_direction.setX(-3);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_atk_neutral,
            sg_damage_atk_neutral,
            sg_knockback_atk_neutral,
            temp_direction,
            1, 1
            ));
    }
    else if (frame == 8) {
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(2, -3));
        }
        else {
            this->scythe->setRelativePos(df::Position(-2, -3));
        }
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::side_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = SIDE_STRIKE;
        this->attack_frames = 24;
        this->cancel_frames = 20;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_90_CCW);
            this->scythe->setRelativePos(df::Position(4, -2));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_270_CW);
            this->scythe->setRelativePos(df::Position(-4, -2));
        }
    }
    else if (frame > 4 && frame < 24 && frame%4 == 0) {
        int temp = frame;
        this->clearHitboxes();

        df::Position temp_relative_pos(0, -4);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(16-temp, -3));
            temp_relative_pos.setX(24-temp);
            temp_direction.setX(3);
        }
        else {
            this->scythe->setRelativePos(df::Position(-16+temp, -3));
            temp_relative_pos.setX(-25+temp);
            temp_direction.setX(-3);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_atk_side,
            sg_damage_atk_side,
            sg_knockback_atk_side,
            temp_direction,
            1, 2
            ));
    }
    else if (frame == 4) {
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(7, -3));
        }
        else {
            this->scythe->setRelativePos(df::Position(-7, -3));
        }
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::up_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = UP_STRIKE;
        this->attack_frames = 20;
        this->cancel_frames = 16;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_0_CCW);
            this->scythe->setRelativePos(df::Position(0, -4));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_0_CW);
            this->scythe->setRelativePos(df::Position(1, -4));
        }
    }
    else if (frame == 10) {
        df::Position temp_relative_pos(0, -10);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(0, -6));
            temp_relative_pos.setX(-2);
            temp_direction.setX(1);
        }
        else {
            this->scythe->setRelativePos(df::Position(1, -6));
            temp_relative_pos.setX(-2);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_atk_up,
            sg_damage_atk_up,
            sg_knockback_atk_up,
            temp_direction,
            5, 1
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::down_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = DOWN_STRIKE;
        this->attack_frames = 20;
        this->cancel_frames = 15;
        if (this->getFacingDirection() == FACING_RIGHT) {
             this->scythe->switchOrientation(SCYTHE_90_CCW);
            this->scythe->setRelativePos(df::Position(0, 0));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_270_CW);
            this->scythe->setRelativePos(df::Position(1, 0));
        }
    }
    else if (frame > 5 && frame < 20 && frame%4 == 0) {
        int temp = frame;
        this->clearHitboxes();

        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(20-temp, 0));
            temp_relative_pos.setX(24-temp);
            temp_direction.setX(1);
        }
        else {
            this->scythe->setRelativePos(df::Position(-19+temp, 0));
            temp_relative_pos.setX(-25+temp);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_atk_down,
            sg_damage_atk_down,
            sg_knockback_atk_down,
            temp_direction,
            1, 3
            ));
    }
    else if (frame == 5) {
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(6, 0));
        }
        else {
            this->scythe->setRelativePos(df::Position(-5, 0));
        }
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::neutral_air(int frame) {
    if (frame == 0) {
        this->attack_type = NEUTRAL_AIR;
        this->attack_frames = 24;
        this->cancel_frames = 18;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_90_CW);
            this->scythe->setRelativePos(df::Position(8, 1));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_270_CCW);
            this->scythe->setRelativePos(df::Position(-7, 1));
        }
    }
    else if (frame > 4 && frame < 24 && frame%4 == 0) {
        int temp = frame/4;
        this->clearHitboxes();

        df::Position temp_relative_pos(0, 6-temp);
        df::Position temp_direction(0, 1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(-4+2*temp, 6-temp));
            temp_relative_pos.setX(3+2*temp);
            temp_direction.setX(-1);
        }
        else {
            this->scythe->setRelativePos(df::Position(5-2*temp, 6-temp));
            temp_relative_pos.setX(-3-2*temp);
            temp_direction.setX(1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_air_neutral,
            sg_damage_air_neutral,
            sg_knockback_air_neutral,
            temp_direction,
            2, 1
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
}


int ScytheGirlChar::back_air(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = BACK_AIR;
        this->attack_frames = 24;
        this->cancel_frames = 12;

        df::Position temp_relative_pos(0, -3);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_270_CCW);
            this->scythe->setRelativePos(df::Position(0, -1));
            temp_relative_pos.setX(-9);
            temp_direction.setX(1);
        }
        else {
            this->scythe->switchOrientation(SCYTHE_90_CW);
            this->scythe->setRelativePos(df::Position(1, -1));
            temp_relative_pos.setX(10);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_air_back,
            sg_damage_air_back,
            sg_knockback_air_back,
            temp_direction,
            1, 3
            ));
    }
    else if (frame == 12) {
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::down_air(int frame) {
    if (frame == 0) {
        this->attack_type = DOWN_AIR;
        this->attack_frames = 24;
        this->cancel_frames = 24;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_180_CCW);
            this->scythe->setRelativePos(df::Position(10, -1));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_180_CW);
            this->scythe->setRelativePos(df::Position(-9, -1));
        }
    }
    else if (frame > 4 && frame < 24 && frame%4 == 0) {
        int temp = frame/4;
        this->clearHitboxes();

        df::Position temp_relative_pos(0, 9-temp);
        df::Position temp_direction(0, 2);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(10, 5-temp));
            temp_relative_pos.setX(7);
            temp_direction.setX(1);
        }
        else {
            this->scythe->setRelativePos(df::Position(-9, 5-temp));
            temp_relative_pos.setX(-9);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_air_down,
            sg_damage_air_down,
            sg_knockback_air_down,
            temp_direction,
            3, 1
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::up_air(int frame) {
    if (frame == 0) {
        this->attack_type = UP_AIR;
        this->attack_frames = 24;
        this->cancel_frames = 24;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_0_CW);
            this->scythe->setRelativePos(df::Position(10, -4));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_0_CCW);
            this->scythe->setRelativePos(df::Position(-9, -4));
        }
    }
    else if (frame > 4 && frame < 24 && frame%4 == 0) {
        int temp = frame/4;
        this->clearHitboxes();

        df::Position temp_relative_pos(0, -14+temp);
        df::Position temp_direction(0, 2);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(10, -10+temp));
            temp_relative_pos.setX(6);
            temp_direction.setX(1);
        }
        else {
            this->scythe->setRelativePos(df::Position(-9, -10+temp));
            temp_relative_pos.setX(-9);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_air_up,
            sg_damage_air_up,
            sg_knockback_air_up,
            temp_direction,
            4, 1
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int ScytheGirlChar::recovery_special(int frame) {
    if (frame == 0) {
        this->attack_type = RECOVERY_SPECIAL;
        this->attack_frames = 40;
        this->cancel_frames = 40;
        this->setYVelocity(-.64);
        this->is_falling = true;
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->switchOrientation(SCYTHE_0_CCW);
            this->scythe->setRelativePos(df::Position(1, -12));
        }
        else {
            this->scythe->switchOrientation(SCYTHE_0_CW);
            this->scythe->setRelativePos(df::Position(0, -12));
        }
        df::Sound *p_sound = df::ResourceManager::getInstance().getSound("jump2");
        p_sound->play();
    }
    else if (frame > 4 && frame < 40 && frame%4 == 0) {
        int temp = frame/4;
        this->clearHitboxes();
        this->setYVelocity(-.64);

        df::Position temp_relative_pos(0, -7-temp);
        df::Position temp_direction(0, -2);
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->scythe->setRelativePos(df::Position(1, -2-temp));
            temp_relative_pos.setX(0);
            temp_direction.setX(1);
        }
        else {
            this->scythe->setRelativePos(df::Position(0, -2-temp));
            temp_relative_pos.setX(-3);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this,
            temp_relative_pos,
            sg_stun_recovery,
            sg_damage_recovery,
            sg_knockback_recovery,
            temp_direction,
            4, 1
            ));
    }
    else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}
