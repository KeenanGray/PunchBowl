#ifndef __LIVESDISPLAY_H__
#define __LIVESDISPLAY_H__

#define LivesDisplay_STRING "Lives : "
#include "ViewObject.h"
#include "Event.h"
#include "EventStep.h"

#include "EventDeath.h"

class LivesDisplay : public df::ViewObject {
private:
    ViewObject *DamageDisplay;
public:
    LivesDisplay();
    virtual void draw();

    //get the damage display
    ViewObject *getDD() const;
};
#endif