#include "LivesDisplay.h"

LivesDisplay::LivesDisplay(){
    setLocation(df::TOP_RIGHT);
    setViewString(LivesDisplay_STRING);
    setColor(df::YELLOW);
    setBorder(false);
    setAltitude(df::MAX_ALTITUDE);

    DamageDisplay = new df::ViewObject(false, df::CENTER_CENTER, this->getColor());
    DamageDisplay->setViewString("Damage");
}

void LivesDisplay::draw(){
    df::ViewObject::draw();
    DamageDisplay->setColor(this->getColor());
    DamageDisplay->setPos(df::Position(this->getPos().getX(), this->getPos().getY() + 1));
}

//get the damage display
df::ViewObject *LivesDisplay::getDD() const{
    return DamageDisplay;
}