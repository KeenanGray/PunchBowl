/**
 * Ultimate Terminal Stage
 *
 * 1v1 Fox Only no items
 */

#ifndef __ULTIMATE_TERMINAL_H__
#define __ULTIMATE_TERMINAL_H__

// Punchbowl headers
#include "Stage.h"


class UltimateTerminal : public Stage {
private:
    int ut_bound_width = 337;
    int ut_bound_height = 48;
public:
    UltimateTerminal();
    ~UltimateTerminal();
};

#endif // __ULTIMATE_TERMINAL_H__
