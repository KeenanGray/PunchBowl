#include "EventDeath.h"

EventDeath::EventDeath(int new_playerNum){
   setType(EVENT_DEATH);
   PlayerNum = new_playerNum;
}

//get the playerID of the selected event
int EventDeath::getPlayerId() const{
    return PlayerNum;
}