/**
 * Character Scythe Girl
 */

#ifndef __SCYTHE_GIRL_H__
#define __SCYTHE_GIRL_H__

// Punchbowl headers
#include "Character.h"

const std::string char_scythe_girl_type = "char_scythe_girl";

class ScytheGirl : public Character {
    private:
        int out();
    public:
        ScytheGirl();

        int eventHandler(const df::Event *p_e);
};

#endif // __SCYTHE_GIRL_H__
