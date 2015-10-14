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
#include "../Platform.h"

UltimateTerminal::UltimateTerminal() {

    // Set type attribute
    setType("stage_ut");

    // Setup sprite
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("stage_ut");

    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(0);
    this->setAltitude(0);
    this->setTransparency('#');

    setStageBounds(df::Box(df::Position(), 480, 96));

    this->starting_positions[0] = df::Position(135, 48);
    this->starting_positions[1] = df::Position(205, 48);
    this->starting_positions[2] = df::Position(275, 48);
    this->starting_positions[3] = df::Position(345, 48);

    this->respawn_position = df::Position(240, 40);

    this->setPos(df::Position(240, 64));

    Platform *p1 = new Platform(ULTIMATE_TERMINAL);
    Platform *p2 = new Platform(ULTIMATE_TERMINAL);

    p1->setPos(df::Position(this->getPos().getX() - 45, this->getPos().getY() - 9));
    p2->setPos(df::Position(this->getPos().getX() + 45, this->getPos().getY() - 9));
}
