#ifndef __EventDeath_H__
#define __EventDeath_H__

#include "Event.h"
#include "Icon.h"

const std::string EVENT_DEATH = "death";

class EventDeath : public df::Event {
private:
    EventDeath(); //Must construct event with a number
    int PlayerNum;

public:
    EventDeath(int new_playerNum);

    //get the playerID of the selected event
    int getPlayerId() const;
};

#endif