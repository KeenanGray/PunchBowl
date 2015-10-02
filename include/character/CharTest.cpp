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
