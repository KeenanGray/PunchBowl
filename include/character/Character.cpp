/**
 * Character class
 */

// C++ Library includes
#include <cmath>

// Dragonfly Engine headers
// Events
#include "EventKeyboard.h"
#include "EventOut.h"
#include "EventStep.h"
// Managers
#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "Character.h"
#include "../stage/UltimateTerminal.h"

Character::Character() {
    // Set type attribute
    setType("char_default");

    // Setup sprite
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("test");

    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(20);

    df::Position pos(96, 16);
    this->setPos(pos);

    this->registerInterest(df::JOYSTICK_EVENT);
    this->registerInterest(df::KEYBOARD_EVENT);
    this->registerInterest(df::STEP_EVENT);
    this->registerInterest(df::OUT_EVENT);

    df::WorldManager &world_manager = df::WorldManager::getInstance();

    world_manager.setViewFollowing(this);

    df::InputManager &input_manager = df::InputManager::getInstance();
    if (input_manager.getJoystickCount() > 0) {
        this->joystick_id = input_manager.getJoysticks()[0];
    }
    this->on_ground = true;
    this->stunned = false;
}

Character::~Character() {

}

int Character::eventHandler(const df::Event *p_e) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getJoystick() != this->joystick_id) {
            return 0;
        }
        return this->controls(p_je);
    } else if (p_e->getType() == df::STEP_EVENT) {
        return this->step();
    } else if (p_e->getType() == df::OUT_EVENT) {
        return this->out();
    }
    return 0;

}

int Character::controls(const df::EventJoystick *p_je) {
    // Axis events
    if (p_je->getAction() == df::AXIS) {
        if (p_je->getAxis() == df::Input::AXIS_X) {
            return this->move(p_je);
        } else if (p_je->getAxis() == df::Input::AXIS_Y) {
            return this->jump(p_je);
        }
    }
    return 0;
}

int Character::jump(const df::EventJoystick *p_je) {
    float temp_val = p_je->getAxisValue();
    if (this->on_ground) {
        if (temp_val < -16) {
            this->setYVelocity(-.32);
            return 1;
        } else {
            this->setYVelocity(0);
        }
    }
    return 0;
}

int Character::move(const df::EventJoystick *p_je) {
    float temp_val = p_je->getAxisValue();
    if (this->on_ground) {
        if (std::abs(temp_val) > 10) {
            this->setXVelocity(temp_val/200.0);
            return 1;
        } else {
            this->setXVelocity(0);
        }
    }
    return 0;
}

int Character::step() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::Position temp_pos = df::Position(this->getPos().getX(), this->getPos().getY()+1);
    df::ObjectList below = world_manager.isCollision(this, temp_pos);
    
    this->on_ground = false;

    if (below.isEmpty()) {
        float y_vel = this->getYVelocity();
        if (y_vel < .32) {
            this->setYVelocity(.04, true);
        }
    } else {
        df::ObjectListIterator li(&below);
        for (li.first(); !li.isDone(); li.next()) {
            df::Object *p_temp_o = li.currentObject();
            if (dynamic_cast <const Stage *> (p_temp_o)) {
                this->setYVelocity(0);
                this->on_ground = true;
            }
        }
    }
    return 1;
}

int Character::out() {

    df::Position pos(96, 16);
    this->setPos(pos);
    return 1;
}
