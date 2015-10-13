/**
 * Character class
 */

// C++ Library includes
#include <cmath>

// Dragonfly Engine headers
// Events
#include "EventOut.h"
#include "EventStep.h"
// Managers
#include "GameManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

#include "utility.h"

// Punchbowl headers
#include "Character.h"
#include "../stage/UltimateTerminal.h"
#include "../Platform.h"
#include "../EventDeath.h"
#include "../Organizer.h"

Character::Character() {
    // Set some default attributes
    setType(char_default_type);
    this->setSolidness(df::SOFT);
    this->setTransparency('#');
    this->current_anim = "undefined_sprite";

    // Register interest for events
    this->registerInterest(df::STEP_EVENT);
    this->registerInterest(df::OUT_EVENT);

    // Initialize character state values
    this->on_ground = true;
    this->on_platform = false;
    this->is_crouched = false;
    this->is_falling = true;

    this->roll_frames = 0;
    this->cancel_roll_frames = DEFAULT_CANCEL_ROLL_FRAMES;
    this->dodge_frames = 0;
    this->stun_frames = 0;
    this->invincible_frames = 0;
    this->attack_frames = 0;
    this->attack_type = UNDEFINED_ATTACK;
    this->cancel_frames = 0;
    this->recovery_available = true;

    this->jump_frames = 0;
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

    this->roll_speed = DEFAULT_ROLL_SPEED;
    this->jump_speed = DEFAULT_JUMP_SPEED;
    this->jump_increment = DEFAULT_JUMP_INCREMENT;
    this->gravity = DEFAULT_GRAVITY;

    this->terminal_velocity = DEFAULT_TERMINAL_VELOCITY;
    this->air_resistance = DEFAULT_AIR_RESISTANCE;

    this->walk_div = DEFAULT_WALK_DIV;
    this->dash_div = DEFAULT_DASH_DIV;
    this->crawl_div = DEFAULT_CRAWL_DIV;
    this->dodge_div = DEFAULT_DODGE_DIV;
    this->di_div = DEFAULT_DI_DIV;

    this->received_y_axis = false;
    this->received_x_axis = false;

    this->hit_sound_cycle = 0;
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
        df::LogManager::getInstance().writeLog(-1, "Character::eventHandler(): Handling JOYSTICK_EVENT");
        return this->controls(p_je);
    }
    else if (p_e->getType() == df::STEP_EVENT) {
        df::LogManager::getInstance().writeLog(-1, "Character::eventHandler(): Handling STEP_EVENT");
        return this->step();
    }
    else if (p_e->getType() == df::OUT_EVENT) {
        df::LogManager::getInstance().writeLog(-1, "Character::eventHandler(): Handling OUT_EVENT");
        return this->out();
    }
    else if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::LogManager::getInstance().writeLog(-1, "Character::eventHandler(): Handling KEYBOARD_EVENT");
        const df::EventKeyboard *p_ke = static_cast<const df::EventKeyboard *> (p_e);
        return this->controlsKeyboard(p_ke);
    }
    return 0;

}

int Character::controls(const df::EventJoystick *p_je) {
    // Cannot do input while locked in an animation or stunned
    if (this->cancel_frames > 0) {
        return 0;
    }
    if (this->stun_frames > 0) {
        return 0;
    }

    // If the character is falling, only DI inputs are allowed
    if (this->is_falling) {
        if (p_je->getAction() == df::AXIS) {
            if (p_je->getAxis() == df::Input::AXIS_X) {
                this->x_axis = p_je->getAxisValue();
                return this->move(p_je);
            }
        }
        // No other inputs recognized
        return 0;
    }
    // If attack frames > 0, this character is in an attack
    // And also cancel frames == 0 so the attack can be cancelled
    if (this->attack_frames > 0) {
        // Inputs capable of cancelling attacks (jumps, down, dodge)
        if (p_je->getAction() == df::AXIS) {
            if (p_je->getAxis() == df::Input::AXIS_Y) {
                // Down
                this->received_y_axis = true;
                this->y_axis = p_je->getAxisValue();
                return this->down(p_je);
            }
            else if (p_je->getAxis() == df::Input::AXIS_X) {
                // No x axis movement is recognized
                this->received_x_axis = true;
                this->x_axis = p_je->getAxisValue();
                return 0;
            }
            else if (p_je->getAxis() == df::Input::AXIS_Z || p_je->getAxis() == df::Input::AXIS_R) {
                // Trigger actions
                if (this->on_ground) {
                    StickDirection temp = this->getJoystickDirection();
                    if (temp == FACING_DOWN) {
                        return this->dodge(p_je);
                    }
                    else if (temp == FACING_LEFT || temp == FACING_RIGHT) {
                        return this->roll(p_je);
                    }
                }
                else {
                    return this->dodge(p_je);
                }
            }
        }
        // Jump actions
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
        df::LogManager::getInstance().writeLog("Axis input is %d, %f", p_je->getAxis(), p_je->getAxisValue());
        if (p_je->getAxis() == df::Input::AXIS_X) {
            this->received_x_axis = true;
            this->x_axis = p_je->getAxisValue();
            return this->move(p_je);
        }
        else if (p_je->getAxis() == df::Input::AXIS_Y) {
            this->received_y_axis = true;
            this->y_axis = p_je->getAxisValue();
            return this->down(p_je);
        }
        else if (p_je->getAxis() == df::Input::AXIS_Z || p_je->getAxis() == df::Input::AXIS_R) {
            StickDirection temp = this->getJoystickDirection();
            if (this->on_ground) {
                if (temp == FACING_DOWN) {
                    return this->dodge(p_je);
                }
                else if (temp == FACING_LEFT || temp == FACING_RIGHT) {
                    return this->roll(p_je);
                }
            }
            else {
                return this->dodge(p_je);
            }
        }
        return 0;
    }
    // button events
    if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
        if (p_je->getButton() == 2) {
            // X Button
            return this->jump(p_je);
        }
        else if (p_je->getButton() == 3) {
            // Y Button
            return this->jump(p_je);
        }
        else if (p_je->getButton() == 0) {
            // B Button
            return this->recovery_special(0);
        }
        else if (p_je->getButton() == 1) {
            // A Button
            // Attack selector
            // Attack initialization is passed a 0 for frame number
            if (this->on_ground) {
                switch (this->getJoystickDirection()) {
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
            }
            else {
                switch (this->getJoystickDirection()) {
                    case FACING_UP:
                        return this->up_air(0);
                    case FACING_DOWN:
                        return this->down_air(0);
                    case FACING_RIGHT:
                        if (this->getFacingDirection() == FACING_RIGHT) {
                            return this->back_air(0);
                        }
                        else {
                            return this->neutral_air(0);
                        }
                    case FACING_LEFT:
                        if (this->getFacingDirection() == FACING_LEFT) {
                            return this->back_air(0);
                        }
                        else {
                            return this->neutral_air(0);
                        }
                    default:
                        return this->neutral_air(0);
                }
            }
        }
        return 0;
    }
    // Joystick buttons held down
    // Currently only used for long jumping from the ground
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

int Character::controlsKeyboard(const df::EventKeyboard *p_ke) {
    // This button should never be used
    // In fact, it literally isn't a recognized button fom SFML (SFML has button ids 0-31 inclusive)
    df::EventJoystick *temp_je = new df::EventJoystick(this->joystick_id, df::JOYSTICK_BUTTON_PRESSED, 64);

    if (p_ke->getAction() == df::KEY_PRESSED) {
        if (p_ke->getKey() == df::Input::A) {
            temp_je = new df::EventJoystick(this->joystick_id, df::JOYSTICK_BUTTON_PRESSED, 1);
        }
        else if (p_ke->getKey() == df::Input::S) {
            temp_je = new df::EventJoystick(this->joystick_id, df::JOYSTICK_BUTTON_PRESSED, 0);
        }
        else {
            return 0;
        }
    }
    else if (p_ke->getAction() == df::KEY_DOWN) {
        if (p_ke->getKey() == df::Input::LEFT) {
            temp_je = new df::EventJoystick(this->joystick_id, df::Input::AXIS_X, -100);
        }
        else if (p_ke->getKey() == df::Input::RIGHT) {
            temp_je = new df::EventJoystick(this->joystick_id, df::Input::AXIS_X, 100);
        }
        else if (p_ke->getKey() == df::Input::UP) {
            temp_je = new df::EventJoystick(this->joystick_id, df::Input::AXIS_Y, -100);
        }
        else if (p_ke->getKey() == df::Input::DOWN) {
            temp_je = new df::EventJoystick(this->joystick_id, df::Input::AXIS_Y, 100);
        }
        else if (p_ke->getKey() == df::Input::C) {
            temp_je = new df::EventJoystick(this->joystick_id, df::Input::AXIS_Y, crouchThreshold + 1);
        }
        else if (p_ke->getKey() == df::Input::D) {
            temp_je = new df::EventJoystick(this->joystick_id, df::Input::AXIS_Z, 100);
        }
        else if (p_ke->getKey() == df::Input::F) {
            temp_je = new df::EventJoystick(this->joystick_id, df::JOYSTICK_BUTTON_DOWN, 3);
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }


    return this->controls(temp_je);
}

int Character::jump(const df::EventJoystick *p_je) {
    // Stops x and y being pressed at the same time from 
    // calling this function twice
    if (!jump_this_frame) {
        // Cancel the current attack
        this->attack_frames = 0;

        // Only one call of this function can be made per frame
        this->jump_this_frame = true;

        // Checks the number of frames the jump button was hld down for.
        // Decides the strength of a jump

        if (this->jump_frames > DEFAULT_SHORTHOP_FRAMES && this->jump_frames < DEFAULT_LONGHOP_FRAMES) {
            // The strength of a jump can be increased by how long 
            // the user holds the button
            // Full hop
            this->setYVelocity(this->jump_increment, true);
            return 1;
        }

        // Initiate a new jump if not currently in a jump
        if (!this->currently_in_jump) {
            // Ground jump or air jump
            if (this->on_ground || this->count_multi_jumps < this->num_multi_jumps) {
                // Set the velocities
                if (this->jump_speed < this->getYVelocity()) {
                    this->setYVelocity(this->jump_speed);
                }
                this->setXVelocity(this->x_axis / this->walk_div);
                // Set appropriate character state variables
                this->count_multi_jumps++;
                this->currently_in_jump = true;
                this->jump_frames = 0;

                df::Sound *p_sound = df::ResourceManager::getInstance().getSound("jump1");
                p_sound->play();

                return 1;
            }
        }
    }
    return 0;
}

int Character::down(const df::EventJoystick *p_je) {

    // If the character is grounded and the joystick is pushed far enough
    if (this->on_ground && this->y_axis > crouchThreshold) {
        // Cancel the current attack
        this->attack_frames = 0;

        // Check whether to crouch or dropdown through platform
        if (this->on_platform && p_je->getAxisValue() > dropDownThreshold) {
            this->setPos(df::Position(this->getPos().getX(), this->getPos().getY() + 1));
        }
        else {
            this->is_crouched = true;
        }
    }
    else {
        // Uncrouch if in air or joystick isn't down
        this->is_crouched = false;
    }

    return 0;
}

int Character::move(const df::EventJoystick *p_je) {
    // Cannot change horizontal velocity while dodging
    if (this->dodge_frames > 0) {
        return 0;
    }
    // Check if the joystick is pushed far enough
    if (std::abs(this->x_axis) > moveThreshold) {
        // Dd ground movement
        if (this->on_ground) {
            // Calculate facing direction
            // That means you cannot change direction in mid-air
            if (this->x_axis > 0) {
                this->facing_direction = FACING_RIGHT;
            }
            else if (this->x_axis < 0) {
                this->facing_direction = FACING_LEFT;
            }
            // Do crawl
            if (this->is_crouched) {
                this->setXVelocity(this->x_axis / this->crawl_div);
                this->current_movement = CRAWLING;
                return 1;
            }
            else {
                int step_count = df::GameManager::getInstance().getStepCount();
                // If joystick was moved fast enough, then begin dashing
                if (std::abs(this->x_axis) > dashThreshold) {
                    // Check if the joystick was moved fast enough
                    if (step_count - this->frame_last_stood <= DEFAULT_DASH_FRAMES) {
                        // Do dash
                        this->setXVelocity(this->x_axis / this->dash_div);
                        this->frame_last_stood = step_count;
                        this->current_movement = DASHING;
                        return 1;
                    }
                }
                // Do walk
                this->setXVelocity(this->x_axis / this->walk_div);
                this->current_movement = WALKING;
                return 1;
            }
        }
        // Do DI calculations in the air
        else if (this->x_axis < 0) {
            if (this->getXVelocity() > -DEFAULT_MAX_DI_SPEED) {
                //this->setXVelocity(temp_val/this->di_div, true);
                this->setXVelocity(this->x_axis / 2000.0, true);
                return 1;
            }
        }
        else if (this->x_axis > 0) {
            if (this->getXVelocity() < DEFAULT_MAX_DI_SPEED) {
                //this->setXVelocity(temp_val/this->di_div, true);
                this->setXVelocity(this->x_axis / 2000.0, true);
                return 1;
            }
        }
    }
    else if (this->on_ground) {
        this->frame_last_stood = df::GameManager::getInstance().getStepCount();
        this->setXVelocity(0);
        if (this->is_crouched) {
            this->current_movement = CROUCHED;
        }
        else {
            this->current_movement = STANDING;
        }
    }
    return 0;
}

int Character::roll(const df::EventJoystick *p_je) {
    if (this->dodge_frames == 0) {
#if defined _WIN32 || defined _WIN64
        if (this->on_ground && std::abs(p_je->getAxisValue()) > triggerThreshold){
            df::LogManager::getInstance().writeLog("windows axis value is %f", std::abs(p_je->getAxisValue()));

#else
        if (this->on_ground && p_je->getAxisValue() > triggerThreshold) {
#endif
            // Cancel the current attack
            this->attack_frames = 0;

            this->roll_frames = DEFAULT_ROLL_FRAMES;
            this->invincible_frames = DEFAULT_ROLL_FRAMES;
            this->cancel_frames = DEFAULT_ROLL_FRAMES+this->cancel_roll_frames;

            StickDirection temp_dir = this->getJoystickDirection();
            if (temp_dir == FACING_RIGHT) {
                this->setXVelocity(-this->roll_speed);
            }
            else if (temp_dir == FACING_LEFT) {
                this->setXVelocity(this->roll_speed);
            }
            return 1;
        }
        }
    return 0;
    }

int Character::dodge(const df::EventJoystick *p_je) {
    if (this->dodge_frames == 0 && this->jump_frames > DEFAULT_SHORTHOP_FRAMES) {

        //Triggers from controllers are read differently based on OS
#if defined _WIN32 || defined _WIN64
        if (std::abs(p_je->getAxisValue()) > triggerThreshold){
            df::LogManager::getInstance().writeLog("windows axis value is %f", std::abs(p_je->getAxisValue()));
#else
        if (p_je->getAxisValue() > triggerThreshold) {
#endif
            // Cancel the current attack
            this->attack_frames = 0;

            this->dodge_frames = DEFAULT_DODGE_FRAMES;
            this->invincible_frames = DEFAULT_DODGE_FRAMES;

            df::Sound *p_sound = df::ResourceManager::getInstance().getSound("dodge");
            p_sound->play();

            if (this->on_ground) {
                this->cancel_frames = DEFAULT_DODGE_FRAMES+6;
            } else {
                // Directional air-dodge
                this->setXVelocity(this->x_axis*1.6/this->dodge_div);
                float temp_y_vel = this->y_axis/this->dodge_div;
                if (this->getYVelocity() < temp_y_vel) {
                    this->setYVelocity(temp_y_vel);
                }
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
    df::Position temp_pos(world_box.getPos().getX(), world_box.getPos().getY() + world_box.getVertical());
    df::Box temp_box(temp_pos, this->getBox().getHorizontal(), 0);
    df::ObjectList obj_below = world_manager.objectsInBox(temp_box);
    // Get objects inside this character
    df::ObjectList obj_inside = world_manager.objectsInBox(world_box);

    df::LogManager::getInstance().writeLog(-1, "Character::step(): Updating name position");
    if (this->name) {
        this->name->updatePosition();
    }

    // If a jump was not attempted in the past frame, a new jump can be attempted
    if (this->jump_this_frame == false) {
        this->currently_in_jump = false;
    }
    // Reset jump frame
    this->jump_this_frame = false;

    // Check if grounded
    this->on_ground = false;
    this->on_platform = false;

    df::LogManager::getInstance().writeLog(-1, "Character::step(): Doing ground calculations");
    if (!obj_below.isEmpty() && this->jump_frames >= DEFAULT_SHORTHOP_FRAMES) {
        df::ObjectListIterator li(&obj_below);
        for (li.first(); !li.isDone(); li.next()) {
            df::Object *p_temp_o = li.currentObject();
            // Ignore self
            if (!(p_temp_o == this) && this != NULL) {
                // The ground cannot be inside the character
                if (!obj_inside.contains(p_temp_o)) {
                    // Do actions for a stage
                    if (dynamic_cast <const Stage *> (p_temp_o)) {
                        df::LogManager::getInstance().writeLog(-1, "Character::step(): Currently on stage");
                        if (this->getYVelocity() > 0) {
                            this->setYVelocity(0);
                        }
                        this->on_ground = true;
                        this->is_falling = false;
                        this->recovery_available = true;
                        this->count_multi_jumps = 0;
                    }
                    // Do actions for a platform
                    else if (dynamic_cast <const Platform *> (p_temp_o)) {
                        df::LogManager::getInstance().writeLog(-1, "Character::step(): Currently on platform");
                        if (this->getYVelocity() > -.1) {
                            if (this->getYVelocity() > 0) {
                                this->setYVelocity(0);
                            }
                            this->on_platform = true;
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
    }


    // Aerial 
    if (!this->on_ground) {
        df::LogManager::getInstance().writeLog(-1, "Character::step(): Doing air calculations");
        if (this->count_multi_jumps == 0) {
            this->count_multi_jumps = 1;
        }
        // Gravity
        float y_vel = this->getYVelocity();
        if (y_vel < this->terminal_velocity) {
            this->setYVelocity(this->gravity, true);
        }
        // Air resistance
        float x_vel = this->getXVelocity();
        if (x_vel < -0.1) {
            this->setXVelocity(this->air_resistance, true);
        }
        else if (x_vel > 0.1) {
            this->setXVelocity(-this->air_resistance, true);
        }
        // Increment jump_frames
        this->jump_frames++;
    }

    // Send neutral joystick actions
    if (!this->received_y_axis) {
        df::EventJoystick *temp = new df::EventJoystick(this->joystick_id, df::Input::AXIS_Y, 0);
        this->controls(temp);
    }
    if (!this->received_x_axis) {
        df::EventJoystick *temp = new df::EventJoystick(this->joystick_id, df::Input::AXIS_X, 0);
        this->controls(temp);
    }
    this->received_y_axis = false;
    this->received_x_axis = false;

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
            // Select the proper attack animation
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
                    case BACK_AIR:
                        this->back_air(this->attack_frames);
                        this->switchToSprite(this->l_air_back, this->air_back_s);
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
            }
            else {
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
                    case BACK_AIR:
                        this->back_air(this->attack_frames);
                        this->switchToSprite(this->r_air_back, this->air_back_s);
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
        }
        else {
            // When the attack is over, reset the animation
            // And clear the hitboxes
            this->clearHitboxes();
            this->attack_type = UNDEFINED_ATTACK;
        }
        return 0;
    }
    if (this->stun_frames > 0) {
        // Select stun animation
        if (this->getFacingDirection() == FACING_LEFT) {
            this->switchToSprite(this->l_stun, this->stun_s);
        }
        else {
            this->switchToSprite(this->r_stun, this->stun_s);
        }
        return 0;
    }
    if (this->currently_in_jump) {
        // Select jumping animation
        if (this->jump_frames < DEFAULT_LONGHOP_FRAMES) {
            if (this->getFacingDirection() == FACING_LEFT) {
                this->switchToSprite(this->l_jump, this->jump_s);
            }
            else {
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
            }
            else if (this->dodge_frames > 0) {
                this->switchToSprite(this->l_dodge, this->dodge_s);
            }
            else if (this->current_movement == STANDING) {
                this->switchToSprite(this->l_stand, this->stand_s);
            }
            else if (this->current_movement == WALKING) {
                this->switchToSprite(this->l_walk, this->walk_s);
            }
            else if (this->current_movement == DASHING) {
                this->switchToSprite(this->l_dash, this->dash_s);
            }
            else if (this->current_movement == CROUCHED) {
                this->switchToSprite(this->l_crouch, this->crouch_s);
            }
            else if (this->current_movement == CRAWLING) {
                this->switchToSprite(this->l_crawl, this->crawl_s);
            }
        }
        else {
            if (this->roll_frames > 0) {
                this->switchToSprite(this->r_roll, this->roll_s);
            }
            else if (this->dodge_frames > 0) {
                this->switchToSprite(this->r_dodge, this->dodge_s);
            }
            else if (this->current_movement == STANDING) {
                this->switchToSprite(this->r_stand, this->stand_s);
            }
            else if (this->current_movement == WALKING) {
                this->switchToSprite(this->r_walk, this->walk_s);
            }
            else if (this->current_movement == DASHING) {
                this->switchToSprite(this->r_dash, this->dash_s);
            }
            else if (this->current_movement == CROUCHED) {
                this->switchToSprite(this->r_crouch, this->crouch_s);
            }
            else if (this->current_movement == CRAWLING) {
                this->switchToSprite(this->r_crawl, this->crawl_s);
            }
        }
        return 0;
    }
    else {
        if (this->getFacingDirection() == FACING_LEFT) {
            if (this->dodge_frames > 0) {
                this->switchToSprite(this->l_dodge, this->dodge_s);
            }
            else if (this->is_falling) {
                this->switchToSprite(this->l_fall, this->fall_s);
            }
            else {
                this->switchToSprite(this->l_air, this->air_s);
            }
        }
        else {
            if (this->dodge_frames > 0) {
                this->switchToSprite(this->r_dodge, this->dodge_s);
            }
            else if (this->is_falling) {
                this->switchToSprite(this->r_fall, this->fall_s);
            }
            else {
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

            // Change the sprite settings
            this->setSprite(sprite);
            this->setSpriteSlowdown(new_sprite_slowdown);
            this->setSpriteIndex(0);

            // Calculate height difference
            int new_height = sprite->getHeight();
            int position_difference = (prev_height + 1) / 2 - (new_height + 1) / 2;

            this->setPos(df::Position(this->getPos().getX(), this->getPos().getY() + position_difference));
            this->current_anim = sprite->getLabel();
        }
    }
}

int Character::hit(Hitbox *p_h) {
    if (this->invincible_frames > 0) {
        df::LogManager::getInstance().writeLog(-1, "Character::hit(): Invincible for %d frames", this->invincible_frames);
        return 0;
    }

    df::LogManager::getInstance().writeLog(-1, "Character::hit(): Hit for %d damage", p_h->getDamage());

    // Instantly stop current attack
    // And cancel any movements currently
    this->roll_frames = 0;
    this->dodge_frames = 0;
    this->attack_frames = 0;
    this->attack_type = UNDEFINED_ATTACK;
    this->is_falling = false;
    this->cancel_frames = 0;
    this->clearHitboxes();

    // Reset recovery move
    this->recovery_available = true;

    // Add stun and damage
    this->stun_frames = p_h->getStun();
    this->setDamage(this->damage + p_h->getDamage());

    // Calculate the horizontal and vertial ratio for the knockback
    df::Position direction = p_h->getDirection();
    int direction_normalization = std::abs(direction.getX()) + std::abs(direction.getY());
    float x_component = float(direction.getX()) / float(direction_normalization);
    float y_component = float(direction.getY()) / float(direction_normalization);
    // Knockback after the damage multiplier is applied
    float adjusted_knockback = p_h->getKnockback()*(1.0 + float(this->damage) / 100.0);

    this->setXVelocity(adjusted_knockback*x_component);
    if (!(this->on_ground && y_component > 0)) {
        this->setYVelocity(std::min(0.9f, adjusted_knockback*y_component));
    }

    std::string hit_sound = "hit1";
    
    if (p_h->getDamage() >= 15) {
        switch (this->hit_sound_cycle) {
            case 1:
                hit_sound = "heavy1";
                this->hit_sound_cycle = 2;
                break;
            case 2:
                hit_sound = "heavy2";
                this->hit_sound_cycle = 3;
                break;
            default:
                hit_sound = "heavy1";
                this->hit_sound_cycle = 2;
                break;
        }
    } else {
        switch (this->hit_sound_cycle) {
            case 1:
                hit_sound = "hit1";
                this->hit_sound_cycle = 2;
                break;
            case 2:
                hit_sound = "hit2";
                this->hit_sound_cycle = 3;
                break;
            case 3:
                hit_sound = "hit3";
                this->hit_sound_cycle = 1;
                break;
            default:
                hit_sound = "hit1";
                this->hit_sound_cycle = 2;
                break;
        }
    }

    df::LogManager::getInstance().writeLog(-1, "Character::hit(): Playing sound %s", hit_sound.c_str());
    df::Sound *p_sound = df::ResourceManager::getInstance().getSound(hit_sound);
    p_sound->play();

    return 1;
}

void Character::clearHitboxes() {
    // Removes all hitboxes
    if (!this->hitboxes.isEmpty()) {
        df::LogManager::getInstance().writeLog(-1, "Character::clearHitboxes(): Clearing hitboxes");
        df::ObjectList to_delete = this->hitboxes;
        df::ObjectListIterator li(&to_delete);
        for (li.first(); !li.isDone(); li.next()) {
            df::Object *p_o = li.currentObject();
            this->hitboxes.remove(p_o);
            delete p_o;
        }
        df::LogManager::getInstance().writeLog(-1, "Character::clearHitboxes(): Hitboxes cleared");
    }
}

//This is being sent to eventhandler so return 1 if success, 0 else
int Character::out() {
    df::WorldManager &w_m = df::WorldManager::getInstance();
    //Send a death event for the player controlling this character
    w_m.onEvent(new EventDeath(joystick_id));
    return 1;
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

int Character::back_air(int frame) {
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

//Get set lives
void Character::setLives(int new_lives){
    lives = new_lives;
}

int Character::getLives() const{
    return lives;
}

void Character::setDamage(int new_damage){
    this->damage = new_damage;

    Organizer &p_org = Organizer::getInstance();
    LivesDisplay** p_tmp_array = p_org.getLivesDisplay();

    for (int i = 0; i < 5; i++){
        if (i == joystick_id){
            if (p_tmp_array[i]) {
                LivesDisplay *tmp_ld = p_tmp_array[i];
                tmp_ld->getDD()->setValue(damage);
            }
        }
    }

}

void Character::setFalling(bool new_falling) {
    this->is_falling = new_falling;
}
