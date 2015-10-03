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

//Game Includes
#include "PlayerName.h"

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
    JUMPING,
    IN_AIR,
};

const float jumpThreshold = -48;
const float moveThreshold = 8;
const float dashThreshold = 80;
const float crouchThreshold = 40;
const float dropDownThreshold = 80;

const int dashingFrames = 4;
// Max number of frames you can hold jump for before a jump becomes a longhop
const int shorthopFrames = 2;
// Max number of frames you can hold a jump for until you reach max jump speed
const int longhopFrames = 9;
// Default jump speed for ground and air jumps
const float jumpSpeedDefault = -0.44;
// Amount of gravity
const float gravityDefault = 0.03;

const std::string char_default_type = "char_default";

class Character : public df::Object {
    private:
        unsigned int joystick_id;

        // Whether or not the character is grounded (either stage or platform)
        bool on_ground;
        // Whether or not the character is on a platform
        bool on_platform;
        // Whether or not the character is crouched
        bool is_crouched;

        // If the character has been knocked down from an attack
        bool knocked_down;
        // The character is currently grabbed onto the ledge
        bool grabbed_ledge;

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
        // The direction the character is currently facing
        StickDirection facing_direction;

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
        // Standing
        std::string l_stand;
        std::string r_stand;
        int stand_s;
        // Walking
        std::string l_walk;
        std::string r_walk;
        int walk_s;
        // Dashing
        std::string l_dash;
        std::string r_dash;
        int dash_s;
        // Crouched
        std::string l_crouch;
        std::string r_crouch;
        int crouch_s;
        // Crawling
        std::string l_crawl;
        std::string r_crawl;
        int crawl_s;
        // Jumping
        std::string l_jump;
        std::string r_jump;
        int jump_s;
        // In Air
        std::string l_air;
        std::string r_air;
        int air_s;
        // Fallen on ground
        std::string l_ground;
        std::string r_ground;
        int ground_s;
        // Grabbed ledge
        std::string l_ledge;
        std::string r_ledge;
        int ledge_s;

        // All the attacks. Oh my god
        // NEUTRAL_JAB,
        std::string l_atk_jab;
        std::string r_atk_jab;
        int atk_jab_s;
        // SIDE_STRIKE,
        std::string l_atk_ss;
        std::string r_atk_ss;
        int atk_ss_s;
        // DOWN_STRIKE,
        std::string l_atk_ds;
        std::string r_atk_ds;
        int atk_ds_s;
        // UP_STRIKE,
        std::string l_atk_us;
        std::string r_atk_us;
        int atk_us_s;
        // DASH_ATTACK,
        std::string l_atk_dash;
        std::string r_atk_dash;
        int atk_dash_s;
        // NEUTRAL_AIR,
        std::string l_atk_nair;
        std::string r_atk_nair;
        int atk_nair_s;
        // FORWARD_AIR,
        std::string l_atk_fair;
        std::string r_atk_fair;
        int atk_fair_s;
        // BACK_AIR,
        std::string l_atk_bair;
        std::string r_atk_bair;
        int atk_bair_s;
        // DOWN_AIR,
        std::string l_atk_dair;
        std::string r_atk_dair;
        int atk_dair_s;
        // UP_AIR,
        std::string l_atk_uair;
        std::string r_atk_uair;
        int atk_uair_s;
        // NEUTRAL_SPECIAL,
        std::string l_atk_nspec;
        std::string r_atk_nspec;
        int atk_nspec_s;
        // SIDE_SPECIAL,
        std::string l_atk_sspec;
        std::string r_atk_sspec;
        int atk_sspec_s;
        // UP_SPECIAL,
        std::string l_atk_uspec;
        std::string r_atk_uspec;
        int atk_uspec_s;
        // DOWN_SPECIAL,
        std::string l_atk_dspec;
        std::string r_atk_dspec;
        int atk_dspec_s;
        // GETUP_ATTACK,
        std::string l_atk_getup;
        std::string r_atk_getup;
        int atk_getup_s;
        // LEDGE_ATTACK,
        std::string l_atk_ledge;
        std::string r_atk_ledge;
        int atk_ledge_s;

    public:
        Character();
        ~Character();

        int eventHandler(const df::Event *p_e);

        virtual int controls(const df::EventJoystick *p_je);

        // 
        virtual int jump(const df::EventJoystick *p_je);

        // Controls behavior of crouching and dropping through platforms
        virtual int down(const df::EventJoystick *p_je);

        virtual int move(const df::EventJoystick *p_je);

        virtual int step();

        // Attacks
        virtual int neutral_jab();
        virtual int side_strike();
        virtual int down_strike();
        virtual int up_strike();
        virtual int dash_attack();
        virtual int neutral_air();
        virtual int forward_air();
        virtual int back_air();
        virtual int down_air();
        virtual int up_air();
        virtual int neutral_special();
        virtual int side_special();
        virtual int up_special();
        virtual int down_special();
        virtual int getup_attack();
        virtual int ledge_attack();

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
