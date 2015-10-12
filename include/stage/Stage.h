/**
 * Stage class header
 *
 * Players fight on these
 */

#ifndef __STAGE_H__
#define __STAGE_H__

// Dragonfly Engine headers
#include "Object.h"

enum Stages
{
    UNDEFINED_STAGE = -1,
    ULTIMATE_TERMINAL,
    VORTEX,
    VACATION,
};

class Stage : public df::Object {
    protected:
        df::Box stage_bounds;

        df::Position starting_positions[4];
        df::Position respawn_position;
    public:
        Stage();
        ~Stage();

        int eventHandler(const df::Event *p_e);
        
        //Getter and setter for stage bounds
        df::Box getStageBounds() const;
        void setStageBounds(df::Box new_stage_bounds);

        df::Position *getStartingPositions();
        df::Position getRespawnPosition();
};

#endif // __STAGE_H__
