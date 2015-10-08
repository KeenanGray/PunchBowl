#ifndef __SELECTEDEVENT_H__
#define __SELECETEDEVENT_H__

#include "Event.h"
#include "Icon.h"

const std::string EVENT_SELECTED = "selected";

class SelectedEvent : public df::Event {
private:
    SelectedEvent(); //Must construct event with an number
    Characters selectedChar;
    int selectedPlayerNum;

public:
    SelectedEvent(int new_playerNum, Characters new_selectedChar);

    //get the character of the selected event
    Characters getSelectedChar() const;

    //get the playerID of the selected event
    int getSelectedPlayerId() const;
};

#endif