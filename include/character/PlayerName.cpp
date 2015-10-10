#include "PlayerName.h"


PlayerName::PlayerName(){
    name = "Default";
    this->setType("PlayerName");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    this->player = NULL;
}

PlayerName::PlayerName(std::string new_name, Character *init_player){
    name = new_name;
    this->setType("PlayerName");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    this->player = init_player;
}

void PlayerName::draw(){
    this->updatePosition();
    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
    graphics_manager.drawString(getPos(), name, df::CENTER_JUSTIFIED, df::RED);
}

void PlayerName::setName(std::string new_name){
    name = new_name;
}
std::string PlayerName::getName() const{
    return name;
}

void PlayerName::updatePosition() {
    //Move name  with character
    if (this->player) {
        this->setPos(df::Position(
            this->player->getPos().getX(), 
            this->player->getPos().getY() - this->player->getSprite()->getHeight()/2 - 1));//name.getOffset().getY()));
    }
}
