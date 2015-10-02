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
    this->registerInterest(df::KEYBOARD_EVENT);

}

Stage::~Stage() {

}

int Stage::eventHandler(const df::Event *p_e) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *keyboard_event = static_cast<const df::EventKeyboard *> (p_e);
        if (keyboard_event->getKey() == df::Input::Q) {
            df::GameManager &game_manager = df::GameManager::getInstance();
            game_manager.setGameOver();
        }
        return 1;
    }
    return 0;

}
