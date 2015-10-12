#include "SelectedEvent.h"

SelectedEvent::SelectedEvent(int new_playerNum, Characters new_selectedChar){
    setType(EVENT_SELECTED);
    selectedChar = new_selectedChar;
    selectedPlayerNum = new_playerNum;

    this->isChar = true;
}

SelectedEvent::SelectedEvent(Stages new_selectedStage){
    setType(EVENT_SELECTED);
    selectedStage = new_selectedStage;

    this->isChar = false;
}

//get the character of the selected event
Characters SelectedEvent::getSelectedChar() const{
    return selectedChar;
}

Stages SelectedEvent::getSelectedStage() const {
    return selectedStage;
}

// Returns true if this is a character selector
// False if it is a stage
bool SelectedEvent::isCharacter() const {
    return this->isChar;
}

//get the playerID of the selected event
int SelectedEvent::getSelectedPlayerId() const{
    return selectedPlayerNum;
}