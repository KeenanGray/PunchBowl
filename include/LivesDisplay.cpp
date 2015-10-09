#include "LivesDisplay.h"

LivesDisplay::LivesDisplay(){
    setLocation(df::TOP_RIGHT);
    setViewString(LivesDisplay_STRING);
    setColor(df::YELLOW);

    registerInterest(df::STEP_EVENT);


}