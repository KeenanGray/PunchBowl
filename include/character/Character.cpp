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

    this->registerInterest(df::JOYSTICK_EVENT);
    this->registerInterest(df::KEYBOARD_EVENT);
    this->registerInterest(df::STEP_EVENT);
    this->registerInterest(df::OUT_EVENT);

    df::InputManager &input_manager = df::InputManager::getInstance();
    if (input_manager.getJoystickCount() > 0) {
        this->joystick_id = input_manager.getJoysticks()[0];
    }

    this->on_ground = true;
    this->stunned = false;

    this->jump_frames = 0;
    this->jump_this_frame = false;

    this->num_multi_jumps = 2;
    this->count_multi_jumps = 0;

    this->x_axis = 0;
    this->y_axis = 0;
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
            this->x_axis = p_je->getAxisValue();
            return this->move(p_je);
        } else if (p_je->getAxis() == df::Input::AXIS_Y) {
            this->y_axis = p_je->getAxisValue();
            return this->jump(p_je);
        }
    }
    // button events
    if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN) {
        if (p_je->getButton() == 2) {
            // X Button
            return this->jump(p_je);
        } else if (p_je->getButton() == 3) {
            // Y Button
            return this->jump(p_je);
        }
    }
    return 0;
}

int Character::jump(const df::EventJoystick *p_je) {
    if (!jump_this_frame) {

        // Whether or not the input registers for a jump
        bool temp_jumped = false;
        if (p_je->getAction() == df::AXIS) {
            temp_jumped = p_je->getAxisValue() < jumpThreshold;
        } else {
            // Button down
            temp_jumped = true;
        }
        if (temp_jumped) {
            // If the controlled are pressed, a jump is currently being attempted
            // Only one call of this function can be made per frame
            this->jump_this_frame = true;
            // Initiate a new jump if not currently in a jump
            if (this->on_ground) {
                // Short hop
                this->setYVelocity(-.32);
                this->setXVelocity(this->x_axis/200.0);
                this->count_multi_jumps++;
                this->currently_in_jump = true;
            } else if (!this->currently_in_jump &&
                this->count_multi_jumps < this->num_multi_jumps
                ) {
                // Air jump
                this->setYVelocity(-.72);
                this->setXVelocity(this->x_axis/200.0);
                this->count_multi_jumps++;
                this->currently_in_jump = true;
            } else if (this->jump_frames > 3 && this->jump_frames < 6) {
                // The strength of a jump can be increased by how long 
                // the user holds the button
                // Full hop
                this->setYVelocity(-0.28, true);
                this->setXVelocity(this->x_axis/200.0);
            }
        }
    }
    return 0;
}

int Character::move(const df::EventJoystick *p_je) {
    float temp_val = p_je->getAxisValue();
    if (std::abs(temp_val) > moveThreshold) {
        if (this->on_ground) {
            this->setXVelocity(temp_val/200.0);
            return 1;
        } else if (std::abs(this->getXVelocity()) < .5) {
            this->setXVelocity(temp_val/4000.0, true);
        }
    } else {
        this->setXVelocity(0);
    }
    return 0;
}

int Character::step() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::Position temp_pos = df::Position(this->getPos().getX(), this->getPos().getY()+1);
    df::ObjectList below = world_manager.isCollision(this, temp_pos);
    
    this->on_ground = false;

    // If a jump was not attempted in the past frame, a new jump can be attempted
    if (this->jump_this_frame == false) {
        this->currently_in_jump = false;
    }
    // Reset jump frame
    this->jump_this_frame = false;

    if (below.isEmpty()) {
        float y_vel = this->getYVelocity();
        if (this->count_multi_jumps == 0) {
            this->count_multi_jumps = 1;
        }
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
                this->jump_frames = 0;
                this->count_multi_jumps = 0;
            }
        }
    }

    if (!this->on_ground) {
        this->jump_frames++;
    }
    return 1;
}

StickDirection Character::getJoystickDirection() const {
    float temp_x = this->x_axis;
    float temp_y = this->y_axis;
    if (std::abs(temp_x) > std::abs(temp_y)) {
        temp_y = 0;
    } else {
        temp_x = 0;
    }
    if (std::abs(temp_x) > moveThreshold) {
        if (temp_x < 0) {
            return FACING_RIGHT;
        } else {
            return FACING_LEFT;
        }
    } else if (std::abs(temp_y) > moveThreshold) {
        if (temp_y < 0) {
            return FACING_UP;
        } else {
            return FACING_DOWN;
        }
    } else {
        return FACING_NEUTRAL;
    }
}

StickDirection Character::getFacingDirection() const {
    float temp_x = this->x_axis;
    if (std::abs(temp_x) > moveThreshold) {
        if (temp_x < 0) {
            return FACING_RIGHT;
        } else {
            return FACING_LEFT;
        }
    }
    return FACING_NEUTRAL;
}

int Character::out() {
    df::Position pos(96, 40);
    this->setPos(pos);
    return 1;
}
