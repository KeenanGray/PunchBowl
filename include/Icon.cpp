#include "Icon.h"

Icon::Icon(std::string new_name){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Icon");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SOFT);

    name = new_name;

    //Set icon spr based on characters name
    df::Sprite *tmp_spr = resource_manager.getSprite(new_name + "-icon");
    setTransparency('#');
    setAltitude(0);
    setSprite(tmp_spr);
}

//get and set name
void Icon::setName(int new_name){
    name = new_name;
}
std::string Icon::getName() const{
    return name;
}

int Icon::eventHandler(const df::Event *p_e){

    return 0;
}
