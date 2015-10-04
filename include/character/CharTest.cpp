/**
 * Character Test
 */

// Dragonfly Engine headers
// Events
#include "EventOut.h"
// Managers
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "CharTest.h"

CharTest::CharTest() {
    this->setType(char_bull_type);
    df::Position pos(48, 20);
    this->setPos(pos);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    world_manager.setViewFollowing(this);

    this->l_stand = "bull-left-spr";
    this->r_stand = "bull-right-spr";
    this->l_walk = "bull-left-walk-spr";
    this->r_walk = "bull-right-walk-spr";
    this->l_dash = "bull-left-dash-spr";
    this->r_dash = "bull-right-dash-spr";
    this->l_crouch = "bull-left-crouch-spr";
    this->r_crouch = "bull-right-crouch-spr";
    this->l_crawl = "bull-left-crawl-spr";
    this->r_crawl = "bull-right-crawl-spr";
    this->l_jump = "bull-left-jump-spr";
    this->r_jump = "bull-right-jump-spr";
    this->l_air = "bull-left-air-spr";
    this->r_air = "bull-right-air-spr";

    this->stand_s = 15;
    this->walk_s = 8;
    this->dash_s = 6;
    this->crouch_s = 0;
    this->crawl_s = 10;
    this->jump_s = 2;
    this->air_s = 0;

    this->setObjectColor(df::RED);

    df::Sprite *p_temp_sprite = resource_manager.getSprite(this->l_stand);
    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(this->stand_s);

    setName(PlayerName("Bull"));

}

CharTest::~CharTest() {

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
    df::Position pos(48, 24);
    this->setPos(pos);
    return 1;
}
