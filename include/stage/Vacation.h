/**
 * Vacation Stage
 */

#ifndef __VACATION_H__
#define __VACATION_H__

// Punchbowl headers
#include "Stage.h"

class Vacation : public Stage {
private:
    int ut_bound_width;
    int ut_bound_height;
public:
    Vacation();
};

#endif // __VACATION_H__
