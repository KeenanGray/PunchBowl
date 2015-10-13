/**
 * Vacation Stage
 */

// Dragonfly Engine headers
// Events
// #include "EventKeyboard.h"
// Managers
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "Vacation.h"
#include "../Platform.h"

Vacation::Vacation() {

    // Set type attribute
    setType("stage_vacation");

    // Setup sprite
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("stage_vacation");

    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(0);
    this->setAltitude(0);
    this->setTransparency('#');

    setStageBounds(df::Box(df::Position(), 480, 96));

    this->starting_positions[0] = df::Position(165, 56);
    this->starting_positions[1] = df::Position(215, 56);
    this->starting_positions[2] = df::Position(265, 56);
    this->starting_positions[3] = df::Position(315, 56);

    this->respawn_position = df::Position(240, 48);

    this->setPos(df::Position(240, 72));

    Platform *p1 = new Platform(VACATION);
    Platform *p2 = new Platform(VACATION);
    Platform *p3 = new Platform(VACATION);

    p1->setPos(df::Position(this->getPos().getX() - 120, this->getPos().getY() - 8));
    p2->setPos(df::Position(this->getPos().getX() + 120, this->getPos().getY() - 8));
    p3->setPos(df::Position(this->getPos().getX(), this->getPos().getY() - 16));
}
