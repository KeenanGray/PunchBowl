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

const float jumpThreshold = -48;
const float moveThreshold = 16;
const float dashThreshold = 80;
// Number of frames t
const int dashingFrames = 3;
// Max number of frames you can hold jump for before a jump becomes a longhop
const int shorthopFrames = 3;
// Max number of frames you can hold a jump for until you reach max jump speed
const int longhopFrames = 6;
// Default jump speed for ground and air jumps
const float jumpSpeedDefault = -0.32;

class Character : public df::Object {
    private:
        unsigned int joystick_id;

        bool on_ground;
        bool stunned;

        // Used to determine whether or not to dash
        int frame_last_stood;
        // Used for determining whether a jump is a short hop or full jump
        int jump_frames;
        // Whether or not jump was called during this frame
        bool jump_this_frame;
        // Whether or not a character is currently in a jump
        bool currently_in_jump;

        // The number of simultaneous jumps the character can do
        int num_multi_jumps;
        // The current jump number the character is on
        int count_multi_jumps;

        df::Position startPos;

        // Stored value of the joystick x axis
        float x_axis;
        // Stored value of the joystick y axis
        float y_axis;

        int out();
        
    protected:
        // The tags of the sprites
        // And their slowdowns
        std::string l_spr;
        int l_spr_s;
        std::string r_spr;
        int r_spr_s;
        std::string l_wspr;
        int l_wspr_s;
        std::string r_wspr;
        int r_wspr_s;

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

};

#endif // __CHARACTER_H__
