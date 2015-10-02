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
    df::Position pos(48, 20);
    this->setPos(pos);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    world_manager.setViewFollowing(this);

    this->l_spr = "bull-left-spr";
    this->r_spr = "bull-right-spr";
    this->l_wspr = "bull-left-wspr";
    this->r_wspr = "bull-right-wspr";
    this->l_dspr = "bull-left-dspr";
    this->r_dspr = "bull-right-dspr";

    this->spr_s = 15;
    this->wspr_s = 8;
    this->dspr_s = 6;

    this->setObjectColor(df::YELLOW);

    df::Sprite *p_temp_sprite = resource_manager.getSprite(this->l_spr);
    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(this->spr_s);

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
