#include "PlayerName.h"


PlayerName::PlayerName(){
    name = "Default";
    setType("PlayerName");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);
    
}

PlayerName::PlayerName(std::string new_name){
    name = new_name;
    setType("PlayerName");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

}

void PlayerName::draw(){
    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
    graphics_manager.drawString(getPos(), name, df::CENTER_JUSTIFIED, df::RED);
}

void PlayerName::setName(std::string new_name){
    name = new_name;
}
std::string PlayerName::getName() const{
    return name;
}
