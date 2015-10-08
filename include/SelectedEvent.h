#ifndef __SELECTEDEVENT_H__
#define __SELECETEDEVENT_H__

#include "Event.h"

const std::string EVENT_SELECTED = "selected";

class SelectedEvent : public df::Event {
private:
    SelectedEvent(); //Must construct event with an number
    std::string selectedName;

public:
    SelectedEvent(std::string selectedName);

    //get the name of the selected event
    std::string getSelectedName() const;
};

#endif