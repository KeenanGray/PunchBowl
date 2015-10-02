/**
 * Ultimate Terminal Stage
 *
 * 1v1 Fox Only no items
 */

#ifndef __ULTIMATE_TERMINAL_H__
#define __ULTIMATE_TERMINAL_H__

// Punchbowl headers
#include "Stage.h"

const int ut_bound_width = 192;
const int ut_bound_height = 72;

class UltimateTerminal : public Stage {
    private:

    public:
        UltimateTerminal();
        ~UltimateTerminal();
};

#endif // __ULTIMATE_TERMINAL_H__
