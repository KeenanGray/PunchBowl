/**
 * Stage class
 */

// Dragonfly Engine headers
// Events
#include "EventKeyboard.h"
// Managers
#include "GameManager.h"
#include "WorldManager.h"


// Punchbowl headers
#include "Stage.h"

Stage::Stage() {

}

Stage::~Stage() {

}

int Stage::eventHandler(const df::Event *p_e) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    return 0;
}

//Getter and setter for stage bounds
df::Box Stage::getStageBounds() const{
    return stage_bounds;
}
void Stage::setStageBounds(df::Box new_stage_bounds){
    stage_bounds = new_stage_bounds;
}