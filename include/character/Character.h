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
    DODGING,
    FALLING,
    ON_GROUND,
    ON_LEDGE,
};

// Various axis thresholds
const float jumpThreshold = -48;
const float moveThreshold = 8;
const float dashThreshold = 80;
const float crouchThreshold = 40;
const float dropDownThreshold = 96;
const float triggerThreshold = -80;

// Frames to roll for
const int rollFrames = 16;
// Number of frames to dodge for
const int dodgeFrames = 32;
// Used to determine how fast you need to move the stick to start dashing
const int dashingFrames = 3;
// Max number of frames you can hold jump for before a jump becomes a longhop
const int shorthopFrames = 2;
// Max number of frames you can hold a jump for until you reach max jump speed
const int longhopFrames = 9;

// Speed when rolling
const float rollSpeed = 1.2;
// Default jump speed for ground and air jumps
const float jumpSpeedDefault = -0.44;
// Amount of gravity
const float gravityDefault = 0.03;

const std::string char_default_type = "char_default";

class Character : public df::Object {
    private:
        PlayerName *name;

        unsigned int joystick_id;

        // Whether or not the character is grounded (either stage or platform)
        bool on_ground;
        // Whether or not the character is on a platform
        bool on_platform;
        // Whether or not the character is crouched
        bool is_crouched;
        // Whether or not the character is in free fall
        bool is_falling;

        // If the character has been knocked down from an attack
        bool knocked_down;
        // The character is currently grabbed onto the ledge
        bool grabbed_ledge;

        // Frames remaining in this character's roll
        int roll_frames;
        // Frames that this character is currently dodging for
        int dodge_frames;
        // Frames that this character are stunned for
        int stun_frames;
        // Frames that this character is invincible for
        int invincible_frames;
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
        // Fallen on ground
        df::Sprite *l_ground;
        df::Sprite *r_ground;
        int ground_s;
        // Grabbed ledge
        df::Sprite *l_ledge;
        df::Sprite *r_ledge;
        int ledge_s;

        // All the attacks. Oh my god
        // NEUTRAL_JAB,
        df::Sprite *l_atk_jab;
        df::Sprite *r_atk_jab;
        int atk_jab_s;
        // SIDE_STRIKE,
        df::Sprite *l_atk_ss;
        df::Sprite *r_atk_ss;
        int atk_ss_s;
        // DOWN_STRIKE,
        df::Sprite *l_atk_ds;
        df::Sprite *r_atk_ds;
        int atk_ds_s;
        // UP_STRIKE,
        df::Sprite *l_atk_us;
        df::Sprite *r_atk_us;
        int atk_us_s;
        // DASH_ATTACK,
        df::Sprite *l_atk_dash;
        df::Sprite *r_atk_dash;
        int atk_dash_s;
        // NEUTRAL_AIR,
        df::Sprite *l_atk_nair;
        df::Sprite *r_atk_nair;
        int atk_nair_s;
        // FORWARD_AIR,
        df::Sprite *l_atk_fair;
        df::Sprite *r_atk_fair;
        int atk_fair_s;
        // BACK_AIR,
        df::Sprite *l_atk_bair;
        df::Sprite *r_atk_bair;
        int atk_bair_s;
        // DOWN_AIR,
        df::Sprite *l_atk_dair;
        df::Sprite *r_atk_dair;
        int atk_dair_s;
        // UP_AIR,
        df::Sprite *l_atk_uair;
        df::Sprite *r_atk_uair;
        int atk_uair_s;
        // NEUTRAL_SPECIAL,
        df::Sprite *l_atk_nspec;
        df::Sprite *r_atk_nspec;
        int atk_nspec_s;
        // SIDE_SPECIAL,
        df::Sprite *l_atk_sspec;
        df::Sprite *r_atk_sspec;
        int atk_sspec_s;
        // UP_SPECIAL,
        df::Sprite *l_atk_uspec;
        df::Sprite *r_atk_uspec;
        int atk_uspec_s;
        // DOWN_SPECIAL,
        df::Sprite *l_atk_dspec;
        df::Sprite *r_atk_dspec;
        int atk_dspec_s;
        // GETUP_ATTACK,
        df::Sprite *l_atk_getup;
        df::Sprite *r_atk_getup;
        int atk_getup_s;
        // LEDGE_ATTACK,
        df::Sprite *l_atk_ledge;
        df::Sprite *r_atk_ledge;
        int atk_ledge_s;

    public:
        Character();

        int eventHandler(const df::Event *p_e);

        virtual int controls(const df::EventJoystick *p_je);

        // 
        virtual int jump(const df::EventJoystick *p_je);

        // Controls behavior of crouching and dropping through platforms
        virtual int down(const df::EventJoystick *p_je);

        virtual int move(const df::EventJoystick *p_je);
        virtual int roll(const df::EventJoystick *p_je);
        virtual int dodge(const df::EventJoystick *p_je);

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
        void switchToSprite(df::Sprite *sprite, int new_sprite_slowdown);

        // Called when this character is hit by an attack
        // Damage takes a flat int
        // Knockback is some float
        virtual int hit(int stun, int damage_dealt, float knockback, df::Position direction);

        //Get and Set Name
        void setName(PlayerName *new_playername);
        PlayerName *getName() const;
};

#endif // __CHARACTER_H__
