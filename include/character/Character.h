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
// Object
#include "Object.h"

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
    DASH_ATTACK,
    NEUTRAL_AIR,
    FORWARD_AIR,
    BACK_AIR,
    DOWN_AIR,
    UP_AIR,
    NEUTRAL_SPECIAL,
    SIDE_SPECIAL,
    UP_SPECIAL,
    DOWN_SPECIAL,
    GETUP_ATTACK,
    LEDGE_ATTACK,
};

enum Movement {
    STANDING = 0,
    WALKING, 
    DASHING,
    CROUCHED,
    CRAWLING,
};

const float jumpThreshold = -48;
const float moveThreshold = 8;
const float dashThreshold = 80;

const int dashingFrames = 4;
// Max number of frames you can hold jump for before a jump becomes a longhop
const int shorthopFrames = 2;
// Max number of frames you can hold a jump for until you reach max jump speed
const int longhopFrames = 9;
// Default jump speed for ground and air jumps
const float jumpSpeedDefault = -0.44;
// Amount of gravity
const float gravityDefault = 0.03;

class Character : public df::Object {
    private:
        unsigned int joystick_id;

        // Whether or no the character is on the ground
        bool on_ground;

        // Frames that this character are stunned for
        int stun_frames;
        // Frames that this character is attacking for
        int attack_frames;
        // The kind of attack the character is doing
        Attack attack_type;
        // Frames until the current animation can be canceled
        int cancel_frames;
        // Whether or not the recovery move is available (up_special)
        bool recovery_available;

        // Used to determine whether or not to dash
        int frame_last_stood;
        // Current state of movement
        Movement current_movement;

        // Used for determining whether a jump is a short hop or full jump
        int jump_frames;
        // Whether or not jump was called during this frame
        bool jump_this_frame;
        // Whether or not a character is currently in a jump
        // This is true while the input for a jump is pressed
        bool currently_in_jump;

        // The number of simultaneous jumps the character can do
        int num_multi_jumps;
        // The current jump number the character is on
        int count_multi_jumps;

        df::Position startPos;

        // Stored value of the joystick x axis
        // Stores last non-zero value
        float x_axis;
        // Stored value of the joystick y axis
        // Stores last non-zero value
        float y_axis;

        // The damage percentage of this character
        int damage;

        int out();
        
    protected:
        // The tags of the sprites
        // And their slowdowns
        // Standing/idle sprites
        std::string current_anim;
        std::string l_spr;
        std::string r_spr;
        int spr_s;
        std::string l_wspr;
        std::string r_wspr;
        int wspr_s;
        std::string l_dspr;
        std::string r_dspr;
        int dspr_s;

    public:
        Character();
        ~Character();

        int eventHandler(const df::Event *p_e);

        virtual int controls(const df::EventJoystick *p_je);

        virtual int jump(const df::EventJoystick *p_je);

        virtual int move(const df::EventJoystick *p_je);

        virtual int step();

        // Returns a joystick direction in one of 4 directions and neutal
        StickDirection getJoystickDirection() const;
        // Returns either left, right, or neutral
        StickDirection getFacingDirection() const;

        // Selects and sets the animation of this character depending on the character's state
        virtual int animationSelector();
        // Switch to a new sprite
        void switchToSprite(std::string sprite_tag, int new_sprite_slowdown);

        // Called when this character is hit by an attack
        // Damage takes a flat int
        // Knockback is some float
        virtual void hit(int stun, int damage_dealt, float knockback, df::Position direction);
};

#endif // __CHARACTER_H__
