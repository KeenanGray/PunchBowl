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

void PlayerName::updateNamePos(df::Position hero_pos){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::Position temp_pos;

    //Keeps PlayerName aligned with Hero
    temp_pos.setX(hero_pos.getX() - 2);
    temp_pos.setY(hero_pos.getY() + 1);

        world_manager.moveObject(this, temp_pos);
        draw();
    }

void PlayerName::draw(){
    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
    graphics_manager.drawString(getPos(), name, df::CENTER_JUSTIFIED, df::RED);
}