#include "StageIcon.h"

StageIcon::StageIcon(Stages new_iconStage, std::string new_name){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Icon");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SOFT);
    setAltitude(4);
    iconStage = new_iconStage;
    name = new_name;
    //Set icon spr based on characters name
    std::string stage_name = "";
        switch (new_iconStage) {
        case ULTIMATE_TERMINAL:
            stage_name = "UT-icon";
            break;
        case VORTEX:
            stage_name = "Vortex-icon";
            break;
        case VACATION:
            stage_name = "Vacation-icon";
            break;
    }
    df::Sprite *tmp_spr = resource_manager.getSprite(stage_name);
    setTransparency('#');
    setAltitude(0);
    setSprite(tmp_spr);
}

//get and set iconChar
void StageIcon::setIconStage(Stages new_iconStage){
    iconStage = new_iconStage;
}
Stages StageIcon::getIconStage() const{
    return iconStage;
}

void StageIcon::draw(){
    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();

    df::Object::draw();

    graphics_manager.drawString(df::Position(this->getPos().getX() - 5,
        this->getPos().getY() + this->getSprite()->getHeight() / 2)
        , name, df::LEFT_JUSTIFIED, df::Color::WHITE, false);
}