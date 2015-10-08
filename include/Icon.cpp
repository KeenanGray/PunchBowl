#include "Icon.h"

Icon::Icon(Characters new_iconChar, std::string new_name){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Icon");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SOFT);

    iconChar = new_iconChar;
    name = new_name;
    //Set icon spr based on characters name
    df::Sprite *tmp_spr = resource_manager.getSprite(new_name + "-icon");
    setTransparency('#');
    setAltitude(0);
    setSprite(tmp_spr);
}

//get and set iconChar
void Icon::setIconChar(Characters new_iconChar){
    iconChar = new_iconChar;
}
Characters Icon::getIconChar() const{
    return iconChar;
}
