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

    this->starting_positions[0] = df::Position(180, 40);
    this->starting_positions[1] = df::Position(230, 50);
    this->starting_positions[2] = df::Position(310, 50);
    this->starting_positions[3] = df::Position(350, 40);

    this->respawn_position = df::Position(270, 60);

    this->setPos(df::Position(270, 72));

    Platform *p1 = new Platform(VORTEX);
    Platform *p2 = new Platform(VORTEX);
    Platform *p3 = new Platform(VORTEX);
    Platform *p4 = new Platform(VORTEX);
    Platform *p5 = new Platform(VORTEX);
    Platform *p6 = new Platform(VORTEX);
    Platform *p7 = new Platform(VORTEX);

    p1->setPos(df::Position(this->getPos().getX() - 40, this->getPos().getY() - 10));
    p2->setPos(df::Position(this->getPos().getX() + 40, this->getPos().getY() - 10));
    p3->setPos(df::Position(this->getPos().getX() - 80, this->getPos().getY() - 20));
    p4->setPos(df::Position(this->getPos().getX() + 80, this->getPos().getY() - 20));
    p5->setPos(df::Position(this->getPos().getX() + 120, this->getPos().getY() - 30));
    p6->setPos(df::Position(this->getPos().getX() - 120, this->getPos().getY() - 30));
    p7->setPos(df::Position(this->getPos().getX(), this->getPos().getY() - 30));
}
