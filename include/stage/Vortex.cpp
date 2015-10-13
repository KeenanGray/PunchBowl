/**
 * Vortex Stage
 */

// Dragonfly Engine headers
// Events
// #include "EventKeyboard.h"
// Managers
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "Vortex.h"
#include "../Platform.h"

Vortex::Vortex() {

    // Set type attribute
    setType("stage_vortex");

    // Setup sprite
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("stage_vortex");

    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(0);

    this->setAltitude(0);
    this->setTransparency('#');


    setStageBounds(df::Box(df::Position(), 540, 96));

    this->starting_positions[0] = df::Position(135, 40);
    this->starting_positions[1] = df::Position(225, 40);
    this->starting_positions[2] = df::Position(315, 40);
    this->starting_positions[3] = df::Position(405, 40);

    this->respawn_position = df::Position(270, 60);

    this->setPos(df::Position(270, 72));

    Platform *p1 = new Platform(VORTEX);
    Platform *p2 = new Platform(VORTEX);
    Platform *p3 = new Platform(VORTEX);
    Platform *p4 = new Platform(VORTEX);
    Platform *p5 = new Platform(VORTEX);
    Platform *p6 = new Platform(VORTEX);

    p1->setPos(df::Position(this->getPos().getX() - 96, this->getPos().getY() - 4));
    p2->setPos(df::Position(this->getPos().getX() + 96, this->getPos().getY() - 4));
    p3->setPos(df::Position(this->getPos().getX() - 48, this->getPos().getY() - 12));
    p4->setPos(df::Position(this->getPos().getX() + 48, this->getPos().getY() - 12));
    p5->setPos(df::Position(this->getPos().getX() + 144, this->getPos().getY() - 12));
    p6->setPos(df::Position(this->getPos().getX() - 144, this->getPos().getY() - 12));
}
