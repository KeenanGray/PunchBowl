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

    this->setTransparency('#');

    this->current_anim = "undefined";

    // Register interest for events
    this->registerInterest(df::JOYSTICK_EVENT);
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
    this->is_falling = false;

    this->knocked_down = false;
    this->grabbed_ledge = false;

    this->roll_frames = 0;
    this->dodge_frames = 0;
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
    this->hitboxes = df::ObjectList();
}

void Character::setJoystickId(unsigned int new_joystick) {
    this->joystick_id = new_joystick;
}

int Character::eventHandler(const df::Event *p_e) {
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
    // Cannot do input while locked in an animation or stunned
    if (this->cancel_frames > 0) {
        return 0;
    } else if (this->stun_frames > 0) {
        // Insert tech recovery here
        return 0;
    }
    if (this->knocked_down) {
        // Ground recovery options
        return 0;
    }
    if (this->grabbed_ledge) {
        return 0;
    }
    if (this->is_falling) {
        if (p_je->getAction() == df::AXIS) {
            if (p_je->getAxis() == df::Input::AXIS_X) {
                this->x_axis = p_je->getAxisValue();
                return this->move(p_je);
            }
        }
        return 0;
    }
    if (this->attack_frames > 0) {
        // Inputs capable of cancelling attacks (jumps, down, dodge)
        if (p_je->getAction() == df::AXIS) {
            if (p_je->getAxis() == df::Input::AXIS_Y) {
                this->y_axis = p_je->getAxisValue();
                if (p_je->getAxisValue() < 0) {
                    return this->jump(p_je);
                } else {
                    return this->down(p_je);
                }
            } else if (p_je->getAxis() == df::Input::AXIS_X) {
                this->x_axis = p_je->getAxisValue();
            } else if (p_je->getAxis() == df::Input::AXIS_Z || p_je->getAxis() == df::Input::AXIS_R) {
                StickDirection temp = this->getJoystickDirection();
                if (this->on_ground) {
                    if (temp == FACING_DOWN) {
                        return this->dodge(p_je);
                    } else if (temp == FACING_LEFT || temp == FACING_RIGHT) {
                        return this->roll(p_je);
                    }
                } else {
                    return this->dodge(p_je);
                }
            }
        }
        if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN || p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
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
            this->x_axis = p_je->getAxisValue();
            return this->move(p_je);
        }
        else if (p_je->getAxis() == df::Input::AXIS_Y) {
            this->y_axis = p_je->getAxisValue();
            if (p_je->getAxisValue() < 0) {
                return this->jump(p_je);
            } else {
                return this->down(p_je);
            }
        } else if (p_je->getAxis() == df::Input::AXIS_Z || p_je->getAxis() == df::Input::AXIS_R) {
            StickDirection temp = this->getJoystickDirection();
            if (this->on_ground) {
                if (temp == FACING_DOWN) {
                    return this->dodge(p_je);
                } else if (temp == FACING_LEFT || temp == FACING_RIGHT) {
                    return this->roll(p_je);
                }
            } else {
                return this->dodge(p_je);
            }
        }
    }
    // button events
    if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
        if (p_je->getButton() == 2) {
            // X Button
            return this->jump(p_je);
        } else if (p_je->getButton() == 3) {
            // Y Button
            return this->jump(p_je);
        } else if (p_je->getButton() == 0) {
            // B Button
            return this->recovery_special(0);
        } else if (p_je->getButton() == 1) {
            // A Button
            if (this->on_ground) {
                switch(this->getJoystickDirection()) {
                    case FACING_NEUTRAL:
                        return this->neutral_jab(0);
                    case FACING_UP:
                        return this->up_strike(0);
                    case FACING_RIGHT:
                        return this->side_strike(0);
                    case FACING_DOWN:
                        return this->down_strike(0);
                    case FACING_LEFT:
                        return this->side_strike(0);
                }
            } else {
                switch(this->getJoystickDirection()) {
                    case FACING_UP:
                        return this->up_air(0);
                    case FACING_DOWN:
                        return this->down_air(0);
                    default:
                        return this->neutral_air(0);
                }
            }
        }
    }
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
        } else if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
            // Button down
            temp_jumped = true;
        } else if (this->jump_frames > shorthopFrames && this->jump_frames < longhopFrames) {
            // The strength of a jump can be increased by how long 
            // the user holds the button
            // Full hop
            this->setYVelocity(-0.08, true);
            return 1;
        }
        if (temp_jumped) {
            this->attack_type = UNDEFINED_ATTACK;
            this->attack_frames = 0;

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
                    return 1;
                }
            } else if (this->jump_frames > shorthopFrames && this->jump_frames < longhopFrames) {
                // The strength of a jump can be increased by how long 
                // the user holds the button
                // Full hop
                this->setYVelocity(-0.08, true);
                return 1;
            }
        }
    }
    return 0;
}

int Character::down(const df::EventJoystick *p_je) {
    if (this->on_ground && p_je->getAxisValue() > crouchThreshold) {
        this->attack_type = UNDEFINED_ATTACK;
            this->attack_frames = 0;

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
    if (this->dodge_frames > 0) {
        return 0;
    }
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
            if (this->getXVelocity() > -.8) {
                this->setXVelocity(temp_val/2000.0, true);
            }
        } else if (temp_val > 0) {
            if (this->getXVelocity() < .8) {
                this->setXVelocity(temp_val/2000.0, true);
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

int Character::roll(const df::EventJoystick *p_je) {
    if (this->dodge_frames == 0) {
        if (this->on_ground && p_je->getAxisValue() > triggerThreshold) {
            this->attack_type = UNDEFINED_ATTACK;
            this->attack_frames = 0;

            this->roll_frames = rollFrames;
            this->cancel_frames = rollFrames+4;

            StickDirection temp_dir = this->getJoystickDirection();
            if (temp_dir == FACING_RIGHT) {
                this->setXVelocity(-rollSpeed);
            } else if (temp_dir == FACING_LEFT) {
                this->setXVelocity(rollSpeed);
            }
            return 1;
        }
    }
    return 0;
}

int Character::dodge(const df::EventJoystick *p_je) {
    if (this->dodge_frames == 0 && this->jump_frames > shorthopFrames) {
        if (p_je->getAxisValue() > triggerThreshold) {
            this->attack_type = UNDEFINED_ATTACK;
            this->attack_frames = 0;

            this->dodge_frames = dodgeFrames;
            this->invincible_frames = dodgeFrames;
            if (this->on_ground) {
                this->cancel_frames = dodgeFrames+5;
            } else {
                this->setXVelocity(this->x_axis/120.0);
                this->setYVelocity(this->y_axis/120.0);
                this->is_falling = true;
            }
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

    //Move name  with character
    name->setPos(df::Position(getPos().getX(), getPos().getY() - getSprite()->getHeight()/2 - 1));//name.getOffset().getY()));
    name->draw();
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
                        this->is_falling = false;
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
                        this->is_falling = false;
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
        if (y_vel < .5) {
            this->setYVelocity(gravityDefault, true);
        }
        float x_vel = this->getXVelocity();
        if (x_vel < 0) {
            this->setXVelocity(+0.004, true);
        } else if (x_vel > 0) {
            this->setXVelocity(-0.004, true);
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
    if (std::abs(temp_x) > joystickThreshold) {
        if (temp_x < 0) {
            return FACING_RIGHT;
        }
        else {
            return FACING_LEFT;
        }
    }
    else if (std::abs(temp_y) > joystickThreshold) {
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
    if (this->roll_frames > 0) {
        this->roll_frames--;
    }
    if (this->dodge_frames > 0) {
        this->dodge_frames--;
    }
    if (this->invincible_frames > 0) {
        this->invincible_frames--;
    }

    // Check if in attack animation
    if (this->attack_type != UNDEFINED_ATTACK) {
        if (this->attack_frames > 0) {
            if (this->getFacingDirection() == FACING_LEFT) {
                switch (this->attack_type) {
                    case NEUTRAL_JAB:
                        this->neutral_jab(this->attack_frames);
                        this->switchToSprite(this->l_atk_neutral, this->atk_neutral_s);
                        break;
                    case SIDE_STRIKE:
                        this->side_strike(this->attack_frames);
                        this->switchToSprite(this->l_atk_side, this->atk_side_s);
                        break;
                    case DOWN_STRIKE:
                        this->down_strike(this->attack_frames);
                        this->switchToSprite(this->l_atk_down, this->atk_down_s);
                        break;
                    case UP_STRIKE:
                        this->up_strike(this->attack_frames);
                        this->switchToSprite(this->l_atk_up, this->atk_up_s);
                        break;
                    case NEUTRAL_AIR:
                        this->neutral_air(this->attack_frames);
                        this->switchToSprite(this->l_air_neutral, this->air_neutral_s);
                        break;
                    case DOWN_AIR:
                        this->down_air(this->attack_frames);
                        this->switchToSprite(this->l_air_down, this->air_down_s);
                        break;
                    case UP_AIR:
                        this->up_air(this->attack_frames);
                        this->switchToSprite(this->l_air_up, this->air_up_s);
                        break;
                    case RECOVERY_SPECIAL:
                        this->recovery_special(this->attack_frames);
                        this->switchToSprite(this->l_recovery, this->recovery_s);
                        break;
                }
            } else {
                switch (this->attack_type) {
                    case NEUTRAL_JAB:
                        this->neutral_jab(this->attack_frames);
                        this->switchToSprite(this->r_atk_neutral, this->atk_neutral_s);
                        break;
                    case SIDE_STRIKE:
                        this->side_strike(this->attack_frames);
                        this->switchToSprite(this->r_atk_side, this->atk_side_s);
                        break;
                    case DOWN_STRIKE:
                        this->down_strike(this->attack_frames);
                        this->switchToSprite(this->r_atk_down, this->atk_down_s);
                        break;
                    case UP_STRIKE:
                        this->up_strike(this->attack_frames);
                        this->switchToSprite(this->r_atk_up, this->atk_up_s);
                        break;
                    case NEUTRAL_AIR:
                        this->neutral_air(this->attack_frames);
                        this->switchToSprite(this->r_air_neutral, this->air_neutral_s);
                        break;
                    case DOWN_AIR:
                        this->down_air(this->attack_frames);
                        this->switchToSprite(this->r_air_down, this->air_down_s);
                        break;
                    case UP_AIR:
                        this->up_air(this->attack_frames);
                        this->switchToSprite(this->r_air_up, this->air_up_s);
                        break;
                    case RECOVERY_SPECIAL:
                        this->recovery_special(this->attack_frames);
                        this->switchToSprite(this->r_recovery, this->recovery_s);
                        break;
                }
            }
            return 0;
        } else {
            this->attack_type = UNDEFINED_ATTACK;
        }
        return 0;
    } else {
        // this->clearHitboxes();
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
            if (this->roll_frames > 0) {
                this->switchToSprite(this->l_roll, this->roll_s);
            } else if (this->dodge_frames > 0) {
                this->switchToSprite(this->l_dodge, this->dodge_s);
            } else if (this->current_movement == STANDING) {
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
            if (this->roll_frames > 0) {
                this->switchToSprite(this->r_roll, this->roll_s);
            } else if (this->dodge_frames > 0) {
                this->switchToSprite(this->r_dodge, this->dodge_s);
            }else if (this->current_movement == STANDING) {
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
            if (this->dodge_frames > 0) {
                this->switchToSprite(this->l_dodge, this->dodge_s);
            } else if (this->is_falling) {
                this->switchToSprite(this->l_fall, this->fall_s);
            } else {
                this->switchToSprite(this->l_air, this->air_s);
            }
        } else {
            if (this->dodge_frames > 0) {
                this->switchToSprite(this->r_dodge, this->dodge_s);
            } else if (this->is_falling) {
                this->switchToSprite(this->r_fall, this->fall_s);
            } else {
                this->switchToSprite(this->r_air, this->air_s);
            }
        }
        return 0;
    }
}

void Character::switchToSprite(df::Sprite *sprite, int new_sprite_slowdown) {
    // Check if not switching to current sprite
    if (sprite) {
        if (sprite->getLabel().compare(this->current_anim) != 0 && this->getType().compare(char_default_type) != 0) {
            // Store previous sprite height
            int prev_height = this->getSprite()->getHeight();
            
            this->setSprite(sprite);
            this->setSpriteSlowdown(new_sprite_slowdown);
            this->setSpriteIndex(0);

            // Calculate height difference
            int new_height = sprite->getHeight();
            int position_difference = (prev_height + 1) / 2 - (new_height + 1) / 2;

            this->setPos(df::Position(this->getPos().getX(), this->getPos().getY()+position_difference));
            this->current_anim = sprite->getLabel();
        }
    }
}

int Character::hit(Hitbox *p_h) {
    if (this->invincible_frames > 0) {
        return 0;
    }

    // Instantly stop current attack
    this->roll_frames = 0;
    this->attack_frames = 0;
    this->attack_type = UNDEFINED_ATTACK;
    this->cancel_frames = 0;

    // Reset recovery moce
    this->recovery_available = true;

    // Add stun and damage
    this->stun_frames = p_h->getStun();
    this->damage += p_h->getDamage();
    
    // Use manhattan distance rather than euclidean distance for direction vectors
    df::Position direction = p_h->getDirection();
    int direction_normalization = std::abs(direction.getX()) + std::abs(direction.getY());
    float x_component = float(direction.getX())/float(direction_normalization);
    float y_component = float(direction.getY())/float(direction_normalization);

    this->setXVelocity(p_h->getKnockback()*x_component*(1.0+float(this->damage)/100.0));
    this->setYVelocity(p_h->getKnockback()*y_component*(1.0+float(this->damage)/100.0));

    return 1;
}

void Character::clearHitboxes() {
    df::ObjectListIterator li(&this->hitboxes);
    while (!li.isDone()) {
        df::Object *p_o = li.currentObject();
        this->hitboxes.remove(p_o);
        delete p_o;
        // li.first();
    }
}

int Character::out() {
    return 0;
}

int Character::neutral_jab(int frame) {
    return 0;
}

int Character::side_strike(int frame) {
    return 0;
}

int Character::down_strike(int frame) {
    return 0;
}

int Character::up_strike(int frame) {
    return 0;
}

int Character::neutral_air(int frame) {
    return 0;
}

int Character::down_air(int frame) {
    return 0;
}

int Character::up_air(int frame) {
    return 0;
}

int Character::recovery_special(int frame) {
    return 0;
}

//Get and Set Name
void Character::setName(PlayerName *new_playername){
    name = new_playername;
}
PlayerName *Character::getName() const{
    return name;
}
