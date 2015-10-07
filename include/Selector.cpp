#include "Selector.h"

Selector::Selector(){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Selector");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SPECTRAL);

    df::Sprite *tmp_spr = resource_manager.getSprite("selector");
    setSprite(tmp_spr);

}

int Selector::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getJoystick() == this->joystickID){
            if (p_je->getAxis() == df::Input::AXIS_X) {
                this->setXVelocity(p_je->getAxisValue() / 100.0);
                return 1;
            }

            if (p_je->getAxis() == df::Input::AXIS_Y) {
                this->setYVelocity(p_je->getAxisValue() / 200.0);
                return 1;
            }
        }
        return 0;

    }
}

//get and set id
void Selector::setJoystickId(int new_id){
    joystickID = new_id;
}
int Selector::getJoystickId() const{
    return joystickID;
}