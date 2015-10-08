#include "Selector.h"

Selector::Selector(){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Selector");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::STEP_EVENT);

    setSolidness(df::SOFT);

    df::Sprite *tmp_spr = resource_manager.getSprite("selector");
    setSprite(tmp_spr);

    this->x_axis_received = false;
    this->y_axis_received = false;
}

int Selector::eventHandler(const df::Event *p_e){
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *p_ke = static_cast<const df::EventKeyboard *> (p_e);
        return this->keyboard(p_ke);
    }
    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getJoystick() == this->joystickID){
            if (p_je->getAxis() == df::Input::AXIS_X) {
                this->x_axis_received = true;
                this->setXVelocity(p_je->getAxisValue() / 100.0);
                return 1;
            }

            if (p_je->getAxis() == df::Input::AXIS_Y) {
                this->y_axis_received = true;
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
                            world_manager.onEvent(new SelectedEvent(playerID, p_icon->getIconChar()));

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
    if (p_e->getType() == df::STEP_EVENT) {
        if (this->x_axis_received) {
            this->setXVelocity(0);
        }
        if (this->y_axis_received) {
            this->setYVelocity(0);
        }
        this->x_axis_received = false;
        this->y_axis_received = false;
    }
    return 0;
}

int Selector::keyboard(const df::EventKeyboard *p_ke) {
    // This button should never be used
    // In fact, it literally isn't a recognized button fom SFML (SFML has button ids 0-31 inclusive)
    df::EventJoystick *temp_je = new df::EventJoystick(this->joystickID, df::JOYSTICK_BUTTON_PRESSED, 64);

    if (p_ke->getAction() == df::KEY_PRESSED) {
        if (p_ke->getKey() == df::Input::A) {
            temp_je = new df::EventJoystick(this->joystickID, df::JOYSTICK_BUTTON_PRESSED, 0);
        } else {
            return 0;
        }
    } else if (p_ke->getAction() == df::KEY_DOWN) {
        if (p_ke->getKey() == df::Input::LEFT) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_X, -100);
        } else if (p_ke->getKey() == df::Input::RIGHT) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_X, 100);
        } else if (p_ke->getKey() == df::Input::UP) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_Y, -100);
        } else if (p_ke->getKey() == df::Input::DOWN) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_Y, 100);
        } else {
            return 0;
        }
    } else {
        return 0;
    }


    return this->eventHandler(temp_je);
}

//get and set joystick
void Selector::setJoystickId(int new_id){
    joystickID = new_id;
}

int Selector::getJoystickId() const{
    return joystickID;
}

//get and set id
void Selector::setPlayerId(int new_id){
    playerID = new_id;
}

int Selector::getPlayerId() const{
    return playerID;
}