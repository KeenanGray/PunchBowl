#ifndef __SELECTEDEVENT_H__
#define __SELECETEDEVENT_H__

#include "Event.h"
#include "Icon.h"
#include "StageIcon.h"

const std::string EVENT_SELECTED = "selected";

class SelectedEvent : public df::Event {
private:
    SelectedEvent(); //Must construct event with an number
    Characters selectedChar;
    Stages selectedStage;

    bool isChar;

    int selectedPlayerNum;

public:
    SelectedEvent(int new_playerNum, Characters new_selectedChar);
    SelectedEvent(Stages new_selectedStage);

    //get the character of the selected event
    Characters getSelectedChar() const;

    //get the stage of the selected event
    Stages getSelectedStage() const;

    // Returns true if this is a character selector
    // False if it is a stage
    bool isCharacter() const;

    //get the playerID of the selected event
    int getSelectedPlayerId() const;
};

#endif