#include "SelectedEvent.h"

SelectedEvent::SelectedEvent(int new_playerNum, Characters new_selectedChar){
    setType(EVENT_SELECTED);
    selectedChar = new_selectedChar;
    selectedPlayerNum = new_playerNum;
}

//get the character of the selected event
Characters SelectedEvent::getSelectedChar() const{
    return selectedChar;
}

//get the playerID of the selected event
int SelectedEvent::getSelectedPlayerId() const{
    return selectedPlayerNum;
}