/**
 * Character Test
 */

// Dragonfly Engine headers
// Events
#include "EventOut.h"
// Managers
#include "WorldManager.h"

// Punchbowl headers
#include "CharTest.h"

CharTest::CharTest() {
    df::Position pos(48, 24);
    this->setPos(pos);

    df::WorldManager &world_manager = df::WorldManager::getInstance();

    world_manager.setViewFollowing(this);

    this->l_spr = "bull-left-spr";
    this->r_spr = "bull-right-spr";
    this->l_wspr = "bull-left-wspr";
    this->r_wspr = "bull-right-wspr";
    
    this->l_spr_s = 15;
    this->r_spr_s = 15;
    this->l_wspr_s = 4;
    this->r_wspr_s = 4;
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
