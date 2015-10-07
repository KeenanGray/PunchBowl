#include "Organizer.h"

Organizer::Organizer(){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Organizer");

    setSolidness(df::SPECTRAL);

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    df::Sprite *tmp_spr = resource_manager.getSprite("Title");
    setSprite(tmp_spr);
    setSpriteSlowdown(25);

    world_manager.setView(df::Box(df::Position(), tmp_spr->getWidth() + 10, tmp_spr->getHeight() + 10));
    world_manager.setBoundary(df::Box(df::Position(), tmp_spr->getWidth() + 10, tmp_spr->getHeight() + 10));

    setPos(df::Position(world_manager.getView().getHorizontal() / 2, world_manager.getView().getVertical() / 2));

    gameStarted = false;

    //character count = 0;
    characterCount = 0;
}

Organizer &Organizer::getInstance(){
    static Organizer *org = new Organizer();
    return *org;
}

int Organizer::eventHandler(const df::Event *p_e){
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *keyboard_event = static_cast<const df::EventKeyboard *> (p_e);
        if (keyboard_event->getKey() == df::Input::Q) {
            if (!gameStarted){
                df::GameManager &game_manager = df::GameManager::getInstance();
                game_manager.setGameOver();
                return 1;
            }
            else{ //Add object back to WM for deletion
                world_manager.insertObject(this);
                df::GameManager &game_manager = df::GameManager::getInstance();
                game_manager.setGameOver();
                return 1;
            }
        }

        if (keyboard_event->getKey() == df::Input::P) {
            if (!gameStarted)
                selectCharacters();
            return 1;
        }
    }
    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN) {
            if (p_je->getButton() == 7) {
                // Start Button
                if (!gameStarted){
                    world_manager.removeObject(this); //Remove the object from WM so it isn't drawn
                    gameStarted = true;
                    return 1;
                }
                else
                    return 1;
            }
            if (p_je->getButton() == 6) {
                // Back Button
                if (!gameStarted){
                    df::GameManager &game_manager = df::GameManager::getInstance();
                    game_manager.setGameOver();
                    return 1;
                }
                else{ //Add object back to WM for deletion
                    world_manager.insertObject(this);
                    df::GameManager &game_manager = df::GameManager::getInstance();
                    game_manager.setGameOver();
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Organizer::startMatch() {
    // Start up the match, at stage, with character 1 and character 2
    //Add an organizer to listen for keyboard input (q for quit);
    Organizer &org = Organizer::getInstance();

    //Load the stage;
    startStage(p_stage);


    /*
    df::Position starting_pos_1(168, 200);
    player1->setPos(starting_pos_1);
    player1->setJoystickId(0);
    // // punching_bag->unregisterInterest(df::JOYSTICK_EVENT);
    // punching_bag->registerInterest(df::KEYBOARD_EVENT);
    player1->setObjectColor(df::GREEN);

    Character *player2 = char2;
    player2->setJoystickId(1);
    //p_c->unregisterInterest(df::JOYSTICK_EVENT);
    //p_c->registerInterest(df::KEYBOARD_EVENT);
    // Character *p_c = new ScytheGirl();

    df::Position starting_pos_2(64, 200);
    player2->setPos(starting_pos_2);
    */
}

void Organizer::startStage(Stage *p_s) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    Platform *p1 = new Platform();
    Platform *p2 = new Platform();

    world_manager.setView(df::Box(df::Position(0, 0), 35, 35));
    world_manager.setBoundary(df::Box(df::Position(0, 0), p_s->getPos().getX() + 10, p_s->getPos().getY()));

    world_manager.setBoundary(df::Box(df::Position(), p_s->getStageBounds().getHorizontal() + 90, p_s->getStageBounds().getVertical()));
    world_manager.setView(df::Box(df::Position(), 96, 32));

    p_s->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() - 30));

    p1->setPos(df::Position(p_s->getPos().getX() - 45, p_s->getPos().getY() - 9));
    p2->setPos(df::Position(p_s->getPos().getX() + 45, p_s->getPos().getY() - 9));
}

void Organizer::selectCharacters(){
    df::InputManager &input_manager = df::InputManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    //Set sprite to blank
    setSpriteIndex(2);
    setSpriteSlowdown(0);
    setAltitude(0);

    int playersNum = input_manager.getJoystickCount();
    //Create character selectors for each player
    for (int i = 0; i < playersNum; i++){
            Selector *tmp_sel = new Selector;
            tmp_sel->setJoystickId(input_manager.getJoysticks()[i]);
            tmp_sel->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 2));
            
            switch (i){
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
            }
        }
    gameStarted = true;
}