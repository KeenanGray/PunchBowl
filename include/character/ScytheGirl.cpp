/**
 * Character ScytheGirl
 */

// Dragonfly Engine headers
// Events
#include "EventOut.h"
// Managers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "ScytheGirl.h"

ScytheGirl::ScytheGirl() {
    this->setType(char_scythe_girl_type);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    this->l_stand   = resource_manager.getSprite("sg-left-spr");
    this->r_stand   = resource_manager.getSprite("sg-right-spr");
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

    this->stand_s = 50;
    this->walk_s = 8;
    this->dash_s = 6;
    this->crouch_s = 0;
    this->crawl_s = 10;
    this->jump_s = 2;
    this->air_s = 0;
    this->roll_s = 4;
    this->dodge_s = 8;
    this->fall_s = 0;

    this->setObjectColor(df::RED);

    setName(new PlayerName("Scythe"));

    this->setSprite(this->l_stand);
    this->setSpriteSlowdown(this->stand_s);
}

int ScytheGirl::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::OUT_EVENT) {
        return this->out();
    } else {
        return Character::eventHandler(p_e);
    }
    return 0;

}

int ScytheGirl::out() {
    df::Position pos(64, 200);
    this->setPos(pos);
    return 1;
}
