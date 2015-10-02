/**
 * Character Test
 */

// Dragonfly Engine headers
// Managers
#include "WorldManager.h"

// Punchbowl headers
#include "CharTest.h"

CharTest::CharTest() {
    df::Position pos(96, 40);
    this->setPos(pos);

    df::WorldManager &world_manager = df::WorldManager::getInstance();

    world_manager.setViewFollowing(this);
}

CharTest::~CharTest() {

}
