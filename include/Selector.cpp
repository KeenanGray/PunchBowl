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
            if (std::abs(p_je->getAxisValue()) > joystickThreshold){
                if (p_je->getAxis() == df::Input::AXIS_X) {
                    this->x_axis_received = true;
                    //Make sure the cursor is within the view 
                    if (this->getPos().getX() > world_manager.getView().getPos().getX() && this->getPos().getX() < world_manager.getView().getHorizontal())
                        this->setXVelocity(p_je->getAxisValue() / 100.0);
                    else
                        this->setPos(df::Position(world_manager.getView().getHorizontal() / 2, this->getPos().getY()));
                    return 1;
                }
            }
            if (p_je->getAxis() == df::Input::AXIS_Y) {
                if (std::abs(p_je->getAxisValue()) > joystickThreshold){
                    this->y_axis_received = true;
                    //Make sure the cursor is within the view 
                    if (this->getPos().getY() > world_manager.getView().getPos().getY() && this->getPos().getY() < world_manager.getView().getVertical())
                        this->setYVelocity(p_je->getAxisValue() / 200.0);
                    else
                        this->setPos(df::Position(this->getPos().getX(), world_manager.getView().getVertical() / 2));
                    return 1;
                }
            }

            if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
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
                            world_manager.markForDelete(this);
                            world_manager.onEvent(new SelectedEvent(playerID, p_icon->getIconChar()));

                            // Disable cursor when character is selected
                            SelectedObj *p_so = new SelectedObj(playerID);
                            p_so->setPos(this->getPos());
                            switch (joystickID){
                                case 0:
                                    p_so->setObjectColor(df::RED);
                                    break;
                                case 1:
                                    p_so->setObjectColor(df::GREEN);
                                    break;
                                case 2:
                                    p_so->setObjectColor(df::YELLOW);
                                    break;
                                case 3:
                                    p_so->setObjectColor(df::BLUE);
                                    break;
                                case 4:
                                    p_so->setObjectColor(df::MAGENTA);
                                    break;
                            }
                            return 1;
                        }
                    }
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
        }
        else {
            return 0;
        }
    }
    else if (p_ke->getAction() == df::KEY_DOWN) {
        if (p_ke->getKey() == df::Input::LEFT) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_X, -100);
        }
        else if (p_ke->getKey() == df::Input::RIGHT) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_X, 100);
        }
        else if (p_ke->getKey() == df::Input::UP) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_Y, -100);
        }
        else if (p_ke->getKey() == df::Input::DOWN) {
            temp_je = new df::EventJoystick(this->joystickID, df::Input::AXIS_Y, 100);
        }
        else {
            return 0;
        }
    }
    else {
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