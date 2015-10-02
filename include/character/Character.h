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

class Character : public df::Object {
    private:
        unsigned int joystick_id;

        bool on_ground;
        bool stunned;

        df::Position startPos;


    public:
        Character();
        ~Character();

        int eventHandler(const df::Event *p_e);

        virtual int controls(const df::EventJoystick *p_je);

        virtual int jump(const df::EventJoystick *p_je);

        virtual int move(const df::EventJoystick *p_je);

        virtual int step();

        int out();
};

#endif // __CHARACTER_H__
