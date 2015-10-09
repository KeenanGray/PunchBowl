/**
 * Ultimate Terminal Stage
 */

// Dragonfly Engine headers
// Events
// #include "EventKeyboard.h"
// Managers
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "UltimateTerminal.h"

UltimateTerminal::UltimateTerminal() {

    // Set type attribute
    setType("stage_ut");

    // Setup sprite
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("stage_ut");

    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(0);
    this->setObjectColor(df::BLUE);

    this->ut_bound_height = 128;
    this->ut_bound_width = p_temp_sprite->getWidth();

    setStageBounds(df::Box(df::Position(), this->ut_bound_width, this->ut_bound_height));

    df::Position pos(this->ut_bound_width / 2, this->ut_bound_height * 2 / 3);
    this->setPos(pos);

    df::WorldManager &world_manager = df::WorldManager::getInstance();
}
