#include "Selector.h"

Selector::Selector(){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Selector");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SOFT);

    df::Sprite *tmp_spr = resource_manager.getSprite("selector");
    setSprite(tmp_spr);

}

int Selector::eventHandler(const df::Event *p_e){
    df::WorldManager &world_manager = df::WorldManager::getInstance();

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

            if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN || p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
                df::LogManager &l_m = df::LogManager::getInstance();
                if (p_je->getButton() == 0) {
                    //A Button

                    //Check for collision with Icon
                    df::ObjectList obj_hit = world_manager.objectsInBox(worldBox(this));

                    df::ObjectListIterator li(&obj_hit);
                    Icon *p_icon;
                    for (li.first(); !li.isDone(); li.next()) {
                        df::Object *p_o = li.currentObject();
                        if (p_icon = dynamic_cast<Icon *> (p_o)) {
                            world_manager.onEvent(new SelectedEvent(p_icon->getName()));

                            //disable joystick
                            setXVelocity(0);
                            setYVelocity(0);
                            setJoystickId(-1);
                            return 1;
                        }
                    }
                    return 1;
                }
            }
            return 0;
        }
    }
}

//get and set id
void Selector::setJoystickId(int new_id){
    joystickID = new_id;
}

int Selector::getJoystickId() const{
    return joystickID;
}