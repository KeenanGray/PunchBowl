#include "SelectedEvent.h"

SelectedEvent::SelectedEvent(std::string new_selectedName){
    setType(EVENT_SELECTED);
    selectedName = new_selectedName;
}

//get the name of the selected event
std::string SelectedEvent::getSelectedName() const{
    return selectedName;
}