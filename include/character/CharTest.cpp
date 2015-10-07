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
#include "CharTest.h"

CharTest::CharTest() {
    this->setType(char_bull_type);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    world_manager.setViewFollowing(this);

    this->l_stand = resource_manager.getSprite("bull-left-spr");
    this->r_stand = resource_manager.getSprite("bull-right-spr");
    this->l_walk = resource_manager.getSprite("bull-left-walk-spr");
    this->r_walk = resource_manager.getSprite("bull-right-walk-spr");
    this->l_dash = resource_manager.getSprite("bull-left-dash-spr");
    this->r_dash = resource_manager.getSprite("bull-right-dash-spr");
    this->l_crouch = resource_manager.getSprite("bull-left-crouch-spr");
    this->r_crouch = resource_manager.getSprite("bull-right-crouch-spr");
    this->l_crawl = resource_manager.getSprite("bull-left-crawl-spr");
    this->r_crawl = resource_manager.getSprite("bull-right-crawl-spr");
    this->l_jump = resource_manager.getSprite("bull-left-jump-spr");
    this->r_jump = resource_manager.getSprite("bull-right-jump-spr");
    this->l_air = resource_manager.getSprite("bull-left-air-spr");
    this->r_air = resource_manager.getSprite("bull-right-air-spr");
    this->l_roll = resource_manager.getSprite("bull-left-roll-spr");
    this->r_roll = resource_manager.getSprite("bull-right-roll-spr");
    this->l_dodge = resource_manager.getSprite("bull-left-dodge-spr");
    this->r_dodge = resource_manager.getSprite("bull-right-dodge-spr");
    this->l_fall = resource_manager.getSprite("bull-left-fall-spr");
    this->r_fall = resource_manager.getSprite("bull-right-fall-spr");
    this->l_stun = resource_manager.getSprite("bull-left-stunned-spr");
    this->r_stun = resource_manager.getSprite("bull-right-stunned-spr");

    this->l_atk_neutral = resource_manager.getSprite("bull-left-atk-neutral-spr");
    this->r_atk_neutral = resource_manager.getSprite("bull-right-atk-neutral-spr");
    this->l_atk_side = resource_manager.getSprite("bull-left-atk-side-spr");
    this->r_atk_side = resource_manager.getSprite("bull-right-atk-side-spr");
    this->l_atk_up = resource_manager.getSprite("bull-left-atk-up-spr");
    this->r_atk_up = resource_manager.getSprite("bull-right-atk-up-spr");


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

    this->setObjectColor(df::RED);
    
    setName(new PlayerName("Bull"));

    this->setSprite(this->l_stand);
    this->setSpriteSlowdown(this->stand_s);
}

int CharTest::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        return this->out();
    } else {
        return Character::eventHandler(p_e);
    }
    return 0;

}

int CharTest::out() {
    df::Position pos(64, 200);
    this->setPos(pos);
    return 1;
}

int CharTest::neutral_jab(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = NEUTRAL_JAB;
        this->attack_frames = 16;
        this->cancel_frames = 12;
    } else if (frame == 12) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(6);
            temp_direction.setX(2);
        } else {
            temp_relative_pos.setX(-6);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this, 
            temp_relative_pos, 
            bull_stun_atk_neutral, 
            bull_damage_atk_neutral, 
            bull_knockback_atk_neutral, 
            temp_direction
            ));
    } else if (frame == 4) {
        this->clearHitboxes();
    }
    return 0;
}

int CharTest::side_strike(int frame) {
    if (frame == 0) {
        if (this->getFacingDirection() == FACING_RIGHT) {
            this->setXVelocity(.2);
        } else {
            this->setXVelocity(-.2);
        }
        this->attack_type = SIDE_STRIKE;
        this->attack_frames = 30;
        this->cancel_frames = 25;
    } else if (frame == 15) {
        df::Position temp_relative_pos(0, -1);
        df::Position temp_direction(0, -1);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(7);
            temp_direction.setX(2);
        } else {
            temp_relative_pos.setX(-7);
            temp_direction.setX(-2);
        }
        this->hitboxes.insert(new Hitbox(
            this, 
            temp_relative_pos, 
            bull_stun_atk_side, 
            bull_damage_atk_side, 
            bull_knockback_atk_side, 
            temp_direction
            ));
    } else if (frame == 10) {
        this->clearHitboxes();
    }
    return 0;
}

int CharTest::up_strike(int frame) {
    if (frame == 0) {
        this->setXVelocity(0);
        this->attack_type = UP_STRIKE;
        this->attack_frames = 20;
        this->cancel_frames = 15;
    } else if (frame == 10) {
        df::Position temp_relative_pos(0, -3);
        df::Position temp_direction(0, -3);
        if (this->getFacingDirection() == FACING_RIGHT) {
            temp_relative_pos.setX(1);
            temp_direction.setX(1);
        } else {
            temp_relative_pos.setX(-1);
            temp_direction.setX(-1);
        }
        this->hitboxes.insert(new Hitbox(
            this, 
            temp_relative_pos, 
            bull_stun_atk_up, 
            bull_damage_atk_up, 
            bull_knockback_atk_up, 
            temp_direction
            ));
    } else if (frame == 15) {
        this->clearHitboxes();
    }
    return 0;
}
