#include "Icon.h"

Icon::Icon(Characters new_iconChar, std::string new_name){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Icon");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SOFT);
    setAltitude(4);
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

void Icon::draw(){
    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();

    df::Object::draw();

    graphics_manager.drawString(df::Position(this->getPos().getX() - 5,
        this->getPos().getY() + this->getSprite()->getHeight() / 2)
        , name, df::LEFT_JUSTIFIED, df::Color::WHITE, false);
}