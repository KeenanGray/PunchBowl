/**
 * Scythe
 */

#ifndef __SCYTHE_H__
#define __SCYTHE_H__

// Dragonfly Engine headers
// Object
#include "Object.h"
#include "ScytheGirlChar.h"

const std::string scythe = "scythe";

class ScytheGirlChar;

enum ScytheOrientation {
    SCYTHE_0_CW,
    SCYTHE_0_CCW,
    SCYTHE_90_CW,
    SCYTHE_90_CCW,
    SCYTHE_180_CW,
    SCYTHE_180_CCW,
    SCYTHE_270_CW,
    SCYTHE_270_CCW,
};

class Scythe : public df::Object {
    private:
        ScytheGirlChar *scythe_girl;
        // Position relative to the scythe girl
        df::Position relative_pos;

        df::Sprite *scythe_0_ccw;
        df::Sprite *scythe_0_cw;
        df::Sprite *scythe_90_ccw;
        df::Sprite *scythe_90_cw;
        df::Sprite *scythe_180_ccw;
        df::Sprite *scythe_180_cw;
        df::Sprite *scythe_270_ccw;
        df::Sprite *scythe_270_cw;

        // Updates this position relative to the scythe girl
        void updatePosition();

    public:
        Scythe(ScytheGirlChar *init_scythe_girl);

        void setRelativePos(df::Position new_pos);

        int eventHandler(const df::Event *p_e);
        virtual void draw();

        void switchOrientation(ScytheOrientation orientation);
};

#endif // __SCYTHE_H__
