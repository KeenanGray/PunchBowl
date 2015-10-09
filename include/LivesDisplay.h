#ifndef __LIVESDISPLAY_H__
#define __LIVESDISPLAY_H__

#define LivesDisplay_STRING "Lives : "
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"

#include "EventDeath.h"

class LivesDisplay : public df::ViewObject {
private:

public:
    LivesDisplay();
};
#endif