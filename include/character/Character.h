/**
 * Character class header
 *
 * Players control these
 */

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

// Dragonfly Engine headers
// Events
#include "EventJoystick.h"
#include "EventKeyboard.h"
// Object
#include "Object.h"

//Game Includes
#include "PlayerName.h"
#include "../Hitbox.h"

// Prototype the hitbox class
class Hitbox;

enum StickDirection {
    FACING_NEUTRAL = 0,
    FACING_UP,
    FACING_RIGHT,
    FACING_DOWN,
    FACING_LEFT,
};

enum Attack {
    UNDEFINED_ATTACK = -1,
    NEUTRAL_JAB,
    SIDE_STRIKE,
    DOWN_STRIKE,
    UP_STRIKE,
    NEUTRAL_AIR,
    BACK_AIR,
    DOWN_AIR,
    UP_AIR,
    RECOVERY_SPECIAL,
};

enum Movement {
    STANDING = 0,
    WALKING, 
    DASHING,
    CROUCHED,
    CRAWLING,
    JUMPING,
    IN_AIR,
    DODGING,
    FALLING,
};

// Various axis thresholds
// These are consistent between characters
const float jumpThreshold = -48;
const float moveThreshold = 16;
const float joystickThreshold = 16;
const float dashThreshold = 96;
const float crouchThreshold = 40;
const float dropDownThreshold = 96;
const float triggerThreshold = 80;

// Default frame and speed data.
// Frames to roll for
const int DEFAULT_ROLL_FRAMES = 16;
// Additional frames to lock input for after rolling
const int DEFAULT_CANCEL_ROLL_FRAMES = 5;
// Number of frames to dodge for
const int DEFAULT_DODGE_FRAMES = 32;
// Used to determine how fast you need to move the stick to start dashing
const int DEFAULT_DASH_FRAMES = 3;
// Max number of frames you can hold jump for before a jump becomes a longhop
const int DEFAULT_SHORTHOP_FRAMES = 2;
// Max number of frames you can hold a jump for until you reach max jump speed
const int DEFAULT_LONGHOP_FRAMES = 9;

// Some characters use their own values for these variables
// Speed when rolling
const float DEFAULT_ROLL_SPEED = 1.0;
// Default jump speed for ground and air jumps
const float DEFAULT_JUMP_SPEED = -0.72;
// Amount to increase y velocity by per jump frame while button is held down
const float DEFAULT_JUMP_INCREMENT = -0.11;
// Amount of gravity
const float DEFAULT_GRAVITY = 0.05;
const float DEFAULT_MAX_DI_SPEED = 0.8;
const float DEFAULT_TERMINAL_VELOCITY = 0.5;
const float DEFAULT_AIR_RESISTANCE = 0.01;

// Used to convert axis values to velocity by division
const float DEFAULT_WALK_DIV = 200.0;
const float DEFAULT_DASH_DIV = 100.0;
const float DEFAULT_CRAWL_DIV = 400.0;
const float DEFAULT_DODGE_DIV = 120.0;
const float DEFAULT_DI_DIV = 2000.0;

const std::string char_default_type = "char_default";

class PlayerName;

class Character : public df::Object {
    private:
        // The name object for the player
        PlayerName *name;

        // The ID of the joystick this character listens to
        unsigned int joystick_id;

     
        df::Position startPos;

        // Stored value of the joystick x axis
        // Stores last non-zero value
        float x_axis;
        // Stored value of the joystick y axis
        // Stores last non-zero value
        float y_axis;

        // The damage percentage of this character
        int damage;

        // Whether or not the axis events for this frame were received.
        bool received_y_axis;
        bool received_x_axis;

        // Called when an object leaves the screen
        int out();
        

        //# of lives
        int lives;

        // For cycling between different hit sounds
        int hit_sound_cycle;

    protected:
        // The number of simultaneous jumps the character can do
        int num_multi_jumps;
        // The current jump number the character is on
        int count_multi_jumps;

        // Frames remaining in this character's roll
        int roll_frames;
        // Frames to add to cancel frames after rolling
        int cancel_roll_frames;
        // Frames that this character is currently dodging for
        int dodge_frames;
        // Frames that this character are stunned for
        int stun_frames;
        // Frames that this character is invincible for
        int invincible_frames;

        // Whether or not the character is grounded (either stage or platform)
        bool on_ground;
        // Whether or not the character is on a platform
        bool on_platform;

        // Used to determine whether or not to dash
        int frame_last_stood;
        // Whether or not the character is crouched
        bool is_crouched;
        // Current state of movement
        Movement current_movement;
        // The direction the character is currently facing
        StickDirection facing_direction;

        // Used for determining whether a jump is a short hop or full jump
        int jump_frames;
        // Whether or not jump was called during this frame
        bool jump_this_frame;
        // Whether or not a character is currently in a jump
        // This is true while the input for a jump is pressed
        bool currently_in_jump;

        // Various movement speed variables
        float roll_speed;
        float jump_speed;
        float jump_increment;
        float gravity;

        // Used when translating a joystick position to a movement speed
        float walk_div;
        float dash_div;
        float crawl_div;
        float dodge_div;
        float di_div;

        // The maximum fall speed
        float terminal_velocity;
        // The change in horizontal velocity when in the air
        float air_resistance;

        // Frames that this character is attacking for
        int attack_frames;
        // The kind of attack the character is doing
        Attack attack_type;
        // Frames until the current animation can be canceled
        int cancel_frames;
        // Whether or not the recovery move is available (up_special)
        bool recovery_available;
        // Whether or not the character is in free fall
        bool is_falling;

        // List of hitboxes generated from attacks
        df::ObjectList hitboxes;

        // Stores the label of the current sprites
        // And their slowdowns
        std::string current_anim;
        // Standing/idle sprites
        // Standing
        df::Sprite *l_stand;
        df::Sprite *r_stand;
        int stand_s;
        // Walking
        df::Sprite *l_walk;
        df::Sprite *r_walk;
        int walk_s;
        // Dashing
        df::Sprite *l_dash;
        df::Sprite *r_dash;
        int dash_s;
        // Crouched
        df::Sprite *l_crouch;
        df::Sprite *r_crouch;
        int crouch_s;
        // Crawling
        df::Sprite *l_crawl;
        df::Sprite *r_crawl;
        int crawl_s;
        // Jumping
        df::Sprite *l_jump;
        df::Sprite *r_jump;
        int jump_s;
        // In Air
        df::Sprite *l_air;
        df::Sprite *r_air;
        int air_s;
        // Rolling
        df::Sprite *l_roll;
        df::Sprite *r_roll;
        int roll_s;
        // Dodging
        df::Sprite *l_dodge;
        df::Sprite *r_dodge;
        int dodge_s;
        // Falling
        df::Sprite *l_fall;
        df::Sprite *r_fall;
        int fall_s;
        // stunned
        df::Sprite *l_stun;
        df::Sprite *r_stun;
        int stun_s;

        // All the attacks. Oh my god
        // NEUTRAL_JAB,
        df::Sprite *l_atk_neutral;
        df::Sprite *r_atk_neutral;
        int atk_neutral_s;
        // SIDE_STRIKE,
        df::Sprite *l_atk_side;
        df::Sprite *r_atk_side;
        int atk_side_s;
        // DOWN_STRIKE,
        df::Sprite *l_atk_down;
        df::Sprite *r_atk_down;
        int atk_down_s;
        // UP_STRIKE,
        df::Sprite *l_atk_up;
        df::Sprite *r_atk_up;
        int atk_up_s;
        // NEUTRAL_AIR,
        df::Sprite *l_air_neutral;
        df::Sprite *r_air_neutral;
        int air_neutral_s;
        // DOWN_AIR,
        df::Sprite *l_air_down;
        df::Sprite *r_air_down;
        int air_down_s;
        // BACK_AIR,
        df::Sprite *l_air_back;
        df::Sprite *r_air_back;
        int air_back_s;
        // UP_AIR,
        df::Sprite *l_air_up;
        df::Sprite *r_air_up;
        int air_up_s;
        // RECOVERY_SPECIAL,
        df::Sprite *l_recovery;
        df::Sprite *r_recovery;
        int recovery_s;

    public:
        // Default constructor
        Character();

        // Sets the joystick id of the character
        void setJoystickId(unsigned int new_joystick);

        // Determines which function to pass the event to
        int eventHandler(const df::Event *p_e);

        // Decides which function to call based on the joystick event
        virtual int controls(const df::EventJoystick *p_je);
        // Creates a joystick event and passes it to controls
        virtual int controlsKeyboard(const df::EventKeyboard *p_ke);

        virtual int jump(const df::EventJoystick *p_je);
        virtual int down(const df::EventJoystick *p_je);
        // Handles all horizontal movement 
        // On the ground: walking, dashing, crawling
        // In the air: DI (Directional influence while in the air)
        virtual int move(const df::EventJoystick *p_je);
        virtual int roll(const df::EventJoystick *p_je);
        virtual int dodge(const df::EventJoystick *p_je);

        virtual int step();

        // Attacks
        // The frame passed in corresponds to this->attack_frames
        // 0 is passed on the first call
        // These should be implemented by individual characters
        virtual int neutral_jab(int frame);
        virtual int side_strike(int frame);
        virtual int down_strike(int frame);
        virtual int up_strike(int frame);
        virtual int neutral_air(int frame);
        virtual int back_air(int frame);
        virtual int down_air(int frame);
        virtual int up_air(int frame);
        virtual int recovery_special(int frame);

        // Returns a joystick direction in one of 4 directions and neutal
        StickDirection getJoystickDirection() const;
        // Returns either left, right, or neutral
        StickDirection getFacingDirection() const;

        // Selects and sets the animation of this character depending on the character's state
        virtual int animationSelector();
        // Switch to a new sprite
        void switchToSprite(df::Sprite *sprite, int new_sprite_slowdown);

        // Called when this character is hit by an attack
        // Damage takes a flat int
        // Knockback is some float
        virtual int hit(Hitbox *p_h);

        // Removes all associated hitboxes
        void clearHitboxes();

        //Get and Set Name
        void setName(PlayerName *new_playername);
        PlayerName *getName() const;

        //Get set lives
        void setLives(int new_lives);
        int getLives() const;

        void setDamage(int new_damage);
        void setFalling(bool new_falling);
};

#endif // __CHARACTER_H__
