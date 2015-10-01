/**
 * Stage class header
 *
 * Players fight on these
 */

#ifndef __STAGE_H__
#define __STAGE_H__

// Dragonfly Engine headers
#include "Object.h"

class Stage : public df::Object {
    private:
        df::Box stage_bounds;

    public:
        Stage();
        ~Stage();

        int eventHandler(const df::Event *p_e);
};

#endif // __STAGE_H__
