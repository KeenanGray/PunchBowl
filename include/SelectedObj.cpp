#include "selectedObj.h"

SelectedObj::SelectedObj(int new_playerId){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("selectedObj");

    joystickID = new_playerId;

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);

    registerInterest(df::STEP_EVENT);

    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    df::Sprite *tmp_spr = resource_manager.getSprite("selectedObj");
    setSprite(tmp_spr);
}

int SelectedObj::eventHandler(const df::Event *p_e){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::InputManager &input_manager = df::InputManager::getInstance();


    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *p_ke = static_cast<const df::EventKeyboard *> (p_e);
        return this->keyboard(p_ke);
    }
    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED) {
            df::LogManager &l_m = df::LogManager::getInstance();
            if (p_je->getJoystick() == joystickID){
                if (p_je->getButton() == 1) {
                    //B Button
                    world_manager.markForDelete(this);

                    //Unselect the character from the Organizer. 
                    world_manager.onEvent(new SelectedEvent(joystickID, NONE));
                    Selector *tmp_sel = new Selector();

                    tmp_sel->setPlayerId(this->joystickID);
                    tmp_sel->setJoystickId(this->joystickID);
                    switch (joystickID){
                        case 0:
                            tmp_sel->setObjectColor(df::RED);
                            break;
                        case 1:
                            tmp_sel->setObjectColor(df::GREEN);
                            break;
                        case 2:
                            tmp_sel->setObjectColor(df::YELLOW);
                            break;
                        case 3:
                            tmp_sel->setObjectColor(df::BLUE);
                            break;
                        case 4:
                            tmp_sel->setObjectColor(df::MAGENTA);
                            tmp_sel->unregisterInterest(df::JOYSTICK_EVENT);
                            tmp_sel->registerInterest(df::KEYBOARD_EVENT);
                            break;
                    }
                    tmp_sel->setPos(this->getPos());
                    return 1;
                }
            }
            return 0;
        }
    }
    if (p_e->getType() == df::STEP_EVENT) {
        Organizer &p_org = Organizer::getInstance();
        if (p_org.getMatchStarted()){
            world_manager.markForDelete(this);
        }
    }
    return 0;
}

int SelectedObj::keyboard(const df::EventKeyboard *p_ke) {
    // This button should never be used
    // In fact, it literally isn't a recognized button fom SFML (SFML has button ids 0-31 inclusive)
    df::EventJoystick *temp_je = new df::EventJoystick(this->joystickID, df::JOYSTICK_BUTTON_PRESSED, 64);

    if (p_ke->getAction() == df::KEY_PRESSED) {
        if (p_ke->getKey() == df::Input::X) {
            temp_je = new df::EventJoystick(this->joystickID, df::JOYSTICK_BUTTON_PRESSED, 1);
        }
        else {
            return 0;
        }
    }

    return this->eventHandler(temp_je);
}
