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

#include "utility.h"

// Punchbowl headers
#include "Character.h"
#include "../stage/UltimateTerminal.h"
#include "../Platform.h"

Character::Character() {
    // Set type attribute
    setType(char_default_type);
    this->setSolidness(df::SOFT);

    // Setup setup default sprites
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::Sprite *p_temp_sprite = resource_manager.getSprite("alien-right-spr");
    this->setSprite(p_temp_sprite);
    this->setSpriteSlowdown(0);
    this->setTransparency('#');

    this->current_anim = "undefined";

    // Register interest for events
    this->registerInterest(df::JOYSTICK_EVENT);
    this->registerInterest(df::KEYBOARD_EVENT);
    this->registerInterest(df::STEP_EVENT);
    this->registerInterest(df::OUT_EVENT);

    // Assign character to a joystick
    df::InputManager &input_manager = df::InputManager::getInstance();
    if (input_manager.getJoystickCount() > 0) {
        this->joystick_id = input_manager.getJoysticks()[0];
    }

    // Initialize character state values
    this->on_ground = true;
    this->on_platform = false;
    this->is_crouched = false;

    this->knocked_down = false;
    this->grabbed_ledge = false;

    this->stun_frames = 0;
    this->attack_frames = 0;
    this->attack_type = UNDEFINED_ATTACK;
    this->cancel_frames = 0;
    this->recovery_available = true;

    this->jump_frames = 1024;
    this->jump_this_frame = false;

    this->num_multi_jumps = 2;
    this->count_multi_jumps = 0;

    this->x_axis = 0;
    this->y_axis = 0;

    this->frame_last_stood = 0;
    this->current_movement = STANDING;
    this->facing_direction = FACING_LEFT;

    this->damage = 0;
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
    }
    else if (p_e->getType() == df::STEP_EVENT) {
        return this->step();
    }
    else if (p_e->getType() == df::OUT_EVENT) {
        return this->out();
    }
    return 0;

}

int Character::controls(const df::EventJoystick *p_je) {
    // Cannot do input while locked in an animation or stunned
    if (this->cancel_frames > 0) {
        return 0;
    } else if (this->stun_frames > 0) {
        // Insert tech recovery here
        return 0;
    }
    if (knocked_down) {
        // Ground recovery options
        return 0;
    }
    if (grabbed_ledge) {
        return 0;
    }
    if (this->attack_frames > 0) {
        // Inputs capable of cancelling attacks (jumps, down, dodge)
        if (p_je->getAction() == df::AXIS) {
            if (p_je->getAxis() == df::Input::AXIS_Y) {
                if (p_je->getAxisValue() != 0) {
                    this->y_axis = p_je->getAxisValue();
                }
                if (p_je->getAxisValue() < 0) {
                    return this->jump(p_je);
                } else {
                    return this->down(p_je);
                }
            }
        }
        if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN) {
            if (p_je->getButton() == 2) {
                // X Button
                return this->jump(p_je);
            }
            else if (p_je->getButton() == 3) {
                // Y Button
                return this->jump(p_je);
            }
        }
        return 0;
    }
    // Standard inputs
    // Axis events
    if (p_je->getAction() == df::AXIS) {
        if (p_je->getAxis() == df::Input::AXIS_X) {
            if (p_je->getAxisValue() != 0) {
                this->x_axis = p_je->getAxisValue();
            }
            return this->move(p_je);
        }
        else if (p_je->getAxis() == df::Input::AXIS_Y) {
            if (p_je->getAxisValue() != 0) {
                this->y_axis = p_je->getAxisValue();
            }
            if (p_je->getAxisValue() < 0) {
                return this->jump(p_je);
            } else {
                return this->down(p_je);
            }
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
        } else if (p_je->getButton() == 3) {
            // B Button
            switch(this->getJoystickDirection()) {
                case FACING_NEUTRAL:
                    return this->neutral_special();
                case FACING_UP:
                    return this->up_special();
                case FACING_RIGHT:
                    return this->side_special();
                case FACING_DOWN:
                    return this->down_special();
                case FACING_LEFT:
                    return this->side_special();
            }
        } else if (p_je->getButton() == 3) {
            // A Button
            if (this->on_ground) {
                switch(this->getJoystickDirection()) {
                    case FACING_NEUTRAL:
                        return this->neutral_jab();
                    case FACING_UP:
                        return this->up_strike();
                    case FACING_RIGHT:
                        return this->side_strike();
                    case FACING_DOWN:
                        return this->down_strike();
                    case FACING_LEFT:
                        return this->side_strike();
                }
            } else {
                switch(this->getJoystickDirection()) {
                    case FACING_NEUTRAL:
                        return this->neutral_air();
                    case FACING_UP:
                        return this->up_air();
                    case FACING_RIGHT:
                        if (this->getFacingDirection() == FACING_RIGHT) {
                            return this->forward_air();
                        } else {
                            return this->back_air();
                        }
                    case FACING_DOWN:
                        return this->down_air();
                    case FACING_LEFT:
                        if (this->getFacingDirection() == FACING_LEFT) {
                            return this->forward_air();
                        } else {
                            return this->back_air();
                        }
                }
            }
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
        }
        else {
            // Button down
            temp_jumped = true;
        }
        if (temp_jumped) {
            // If the controlled are pressed, a jump is currently being attempted
            // Only one call of this function can be made per frame
            this->jump_this_frame = true;
            // Initiate a new jump if not currently in a jump
            if (!this->currently_in_jump) {
                // Ground jump or air jump
                if (this->on_ground || this->count_multi_jumps < this->num_multi_jumps) {
                    this->setYVelocity(jumpSpeedDefault);
                    this->setXVelocity(this->x_axis/200.0);
                    this->count_multi_jumps++;
                    this->currently_in_jump = true;
                    this->jump_frames = 0;
                }
            } else if (this->jump_frames > shorthopFrames && this->jump_frames < longhopFrames) {
                // The strength of a jump can be increased by how long 
                // the user holds the button
                // Full hop
                this->setYVelocity(-0.08, true);
            }
        }
    }
    return 0;
}

int Character::down(const df::EventJoystick *p_je) {
    if (this->on_ground && p_je->getAxisValue() > crouchThreshold) {
        if (this->on_platform && p_je->getAxisValue() > dropDownThreshold) {
            this->setPos(df::Position(this->getPos().getX(), this->getPos().getY()+1));
        } else {
            this->is_crouched = true;
        }
    } else {
        this->is_crouched = false;
    }

    return 0;
}

int Character::move(const df::EventJoystick *p_je) {
    float temp_val = p_je->getAxisValue();
    if (std::abs(temp_val) > moveThreshold) {
        if (this->on_ground) {
            if (temp_val > 0) {
                this->facing_direction = FACING_RIGHT;
            } else {
                this->facing_direction = FACING_LEFT;
            }
            if (this->is_crouched) {
                this->setXVelocity(temp_val/400.0);
                this->current_movement = CRAWLING;
            } else {
                this->setXVelocity(temp_val/200.0);
                this->current_movement = WALKING;
                int step_count = df::GameManager::getInstance().getStepCount();
                // If joystick was moved fast enough, then begin dashing
                if (std::abs(temp_val) > dashThreshold) {
                    if (step_count - this->frame_last_stood <= dashingFrames) {
                        this->setXVelocity(temp_val/100.0);
                        this->frame_last_stood = step_count;
                        this->current_movement = DASHING;
                    }
                }
            }
        } else if (temp_val < 0) {
            if (this->getXVelocity() > -.5) {
                this->setXVelocity(temp_val/4000.0, true);
            }
        } else if (temp_val > 0) {
            if (this->getXVelocity() < .5) {
                this->setXVelocity(temp_val/4000.0, true);
            }
        }
    } else if (this->on_ground) {
        this->frame_last_stood = df::GameManager::getInstance().getStepCount();
        this->setXVelocity(0);
        if (this->is_crouched) {
            this->current_movement = CROUCHED;
        } else {
            this->current_movement = STANDING;
        }
    }
    return 0;
}

int Character::step() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    df::Box world_box = df::worldBox(this);
    // Get objects below this character
    df::Position temp_pos(world_box.getPos().getX(), world_box.getPos().getY()+world_box.getVertical());
    df::Box temp_box(temp_pos, this->getBox().getHorizontal(), 0);
    df::ObjectList obj_below = world_manager.objectsInBox(temp_box);
    // Get objects inside this character
    df::ObjectList obj_inside = world_manager.objectsInBox(world_box);

    // If a jump was not attempted in the past frame, a new jump can be attempted
    if (this->jump_this_frame == false) {
        this->currently_in_jump = false;
    }
    // Reset jump frame
    this->jump_this_frame = false;

    // Check if grounded
    this->on_ground = false;
    this->on_platform = false;
    if (!obj_below.isEmpty() && this->jump_frames >= shorthopFrames) {
        df::ObjectListIterator li(&obj_below);
        for (li.first(); !li.isDone(); li.next()) {
            df::Object *p_temp_o = li.currentObject();
            if (!(p_temp_o == this)) {
                if (!obj_inside.contains(p_temp_o)) {
                    if (dynamic_cast <const Stage *> (p_temp_o)) {
                        if (this->getYVelocity() > 0) {
                            this->setYVelocity(0);
                        }
                        this->on_ground = true;
                        this->recovery_available = true;
                        this->count_multi_jumps = 0;
                        // TODO: Tech recovery when touching ground
                    } else if (dynamic_cast <const Platform *> (p_temp_o)) {
                        this->on_platform = true;
                        // Find some way to reduce this duplicate code
                        if (this->getYVelocity() > 0) {
                            this->setYVelocity(0);
                        }
                        this->on_ground = true;
                        this->recovery_available = true;
                        this->count_multi_jumps = 0;
                        // TODO: Tech recovery when touching ground
                    }
                }
            }
        }
    }

    // Aerial 
    if (!this->on_ground) {
        if (this->count_multi_jumps == 0) {
            this->count_multi_jumps = 1;
        }
        // Gravity
        float y_vel = this->getYVelocity();
        if (y_vel < .32) {
            this->setYVelocity(gravityDefault, true);
        }
        this->jump_frames++;
    }

    // Determine which animation to use
    this->animationSelector();

    return 1;
}

StickDirection Character::getJoystickDirection() const {
    float temp_x = this->x_axis;
    float temp_y = this->y_axis;
    if (std::abs(temp_x) > std::abs(temp_y)) {
        temp_y = 0;
    }
    else {
        temp_x = 0;
    }
    if (std::abs(temp_x) > moveThreshold) {
        if (temp_x < 0) {
            return FACING_RIGHT;
        }
        else {
            return FACING_LEFT;
        }
    }
    else if (std::abs(temp_y) > moveThreshold) {
        if (temp_y < 0) {
            return FACING_UP;
        }
        else {
            return FACING_DOWN;
        }
    }
    else {
        return FACING_NEUTRAL;
    }
}

StickDirection Character::getFacingDirection() const {
    return this->facing_direction;
}

int Character::animationSelector() {

    // Decrement animation frames
    if (this->stun_frames > 0) {
        this->stun_frames--;
    }
    if (this->attack_frames > 0) {
        this->attack_frames--;
    }
    if (this->cancel_frames > 0) {
        this->cancel_frames--; 
    }

    // Check if in attack animation
    if (this->attack_type != UNDEFINED_ATTACK) {
        if (this->attack_frames > 0) {
            // Select some attack animation
        } else {
            this->attack_type = UNDEFINED_ATTACK;
        }
        return 0;
    }
    if (this->stun_frames > 0) {
        // Select stun animation
        return 0;
    }
    if (this->currently_in_jump) {
        if (this->jump_frames < longhopFrames) {
            if (this->getFacingDirection() == FACING_LEFT) {
                this->switchToSprite(this->l_jump, this->jump_s);
            } else {
                this->switchToSprite(this->r_jump, this->jump_s);
            }
            return 0;
        }
    }
    if (this->on_ground) {
        // Select some ground animation
        if (this->getFacingDirection() == FACING_LEFT) {
            if (this->current_movement == STANDING) {
                this->switchToSprite(this->l_stand, this->stand_s);
            } else if (this->current_movement == WALKING) {
                this->switchToSprite(this->l_walk, this->walk_s);
            } else if (this->current_movement == DASHING) {
                this->switchToSprite(this->l_dash, this->dash_s);
            } else if (this->current_movement == CROUCHED) {
                this->switchToSprite(this->l_crouch, this->crouch_s);
            } else if (this->current_movement == CRAWLING) {
                this->switchToSprite(this->l_crawl, this->crawl_s);
            }
        } else {
            if (this->current_movement == STANDING) {
                this->switchToSprite(this->r_stand, this->stand_s);
            } else if (this->current_movement == WALKING) {
                this->switchToSprite(this->r_walk, this->walk_s);
            } else if (this->current_movement == DASHING) {
                this->switchToSprite(this->r_dash, this->dash_s);
            } else if (this->current_movement == CROUCHED) {
                this->switchToSprite(this->r_crouch, this->crouch_s);
            } else if (this->current_movement == CRAWLING) {
                this->switchToSprite(this->r_crawl, this->crawl_s);
            }
        }
    } else {
        if (this->getFacingDirection() == FACING_LEFT) {
            this->switchToSprite(this->l_air, this->air_s);
        } else {
            this->switchToSprite(this->r_air, this->air_s);
        }
        return 0;
    }
}

void Character::switchToSprite(std::string sprite_tag, int new_sprite_slowdown) {
    // Check if not switching to current sprite
    if (sprite_tag.compare(this->current_anim) != 0 && this->getType().compare(char_default_type) != 0) {
        this->setSpriteIndex(0);
        // Store previous sprite height
        int prev_height = this->getSprite()->getHeight();
        
        df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
        df::Sprite *p_temp_sprite = resource_manager.getSprite(sprite_tag);
        setSprite(p_temp_sprite);
        setSpriteSlowdown(new_sprite_slowdown);

        // Calculate height difference
        int new_height = p_temp_sprite->getHeight();
        int position_difference = (prev_height + 1) / 2 - (new_height + 1) / 2;

        this->setPos(df::Position(this->getPos().getX(), this->getPos().getY()+position_difference));
        this->current_anim = sprite_tag;
    }
}

void Character::hit(int stun, int damage_dealt, float knockback, df::Position direction) {

    // Instantly stop current attack
    this->attack_frames = 0;
    this->attack_type = UNDEFINED_ATTACK;
    this->cancel_frames = 0;

    // Reset recovery moce
    this->recovery_available = true;

    // Add stun and damage
    this->stun_frames = stun;
    this->damage += damage_dealt;
    // Use manhattan distance rather than euclidean distance for direction vectors
    int direction_normalization = direction.getX() + direction.getY();
    float x_component = float(direction.getX())/float(direction_normalization);
    float y_component = float(direction.getY())/float(direction_normalization);

    this->setXVelocity(knockback*x_component*(1.0+float(this->damage)/100));
    this->setXVelocity(knockback*y_component*(1.0+float(this->damage)/100));
}

int Character::out() {
    return 0;
}

int Character::neutral_jab() {
    return 0;
}

int Character::side_strike() {
    return 0;
}

int Character::down_strike() {
    return 0;
}

int Character::up_strike() {
    return 0;
}

int Character::dash_attack() {
    return 0;
}

int Character::neutral_air() {
    return 0;
}

int Character::forward_air() {
    return 0;
}

int Character::back_air() {
    return 0;
}

int Character::down_air() {
    return 0;
}

int Character::up_air() {
    return 0;
}

int Character::neutral_special() {
    return 0;
}

int Character::side_special() {
    return 0;
}

int Character::up_special() {
    return 0;
}

int Character::down_special() {
    return 0;
}

int Character::getup_attack() {
    return 0;
}

int Character::ledge_attack() {
    return 0;
}


