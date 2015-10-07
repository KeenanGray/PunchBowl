#include "Organizer.h"

Organizer::Organizer(){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Organizer");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);


    // df::Sprite *tmp_spr = resource_manager.getSprite("Title");
    df::Sprite *tmp_spr = resource_manager.getSprite("test");
    setSprite(tmp_spr);
    setSpriteSlowdown(25);

    world_manager.setView(df::Box(df::Position(), tmp_spr->getWidth() + 10, tmp_spr->getHeight() + 10));
    world_manager.setBoundary(df::Box(df::Position(), tmp_spr->getWidth() + 10, tmp_spr->getHeight() + 10));

    setPos(df::Position(world_manager.getView().getHorizontal() / 2, world_manager.getView().getVertical() / 2));

    gameStarted = false;
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
            if (!gameStarted){
                world_manager.removeObject(this); //Remove the object from WM so it isn't drawn
                startUpGame();
                gameStarted = true;
                return 1;
            }
            else
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
                    startUpGame();
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

void Organizer::startUpGame() {
    // Start up the game stuff
    //Add an organizer to listen for keyboard input (q for quit);
    Organizer &org = Organizer::getInstance();

    //Load the stage;
    Stage *p_s = new UltimateTerminal();
    startStage(p_s);

    Character *punching_bag = new CharTest();

    df::Position starting_pos_1(168, 200);
    punching_bag->setPos(starting_pos_1);
    punching_bag->setJoystickId(1);
    // // punching_bag->unregisterInterest(df::JOYSTICK_EVENT);
    // punching_bag->registerInterest(df::KEYBOARD_EVENT);
    punching_bag->setObjectColor(df::GREEN);

    Character *p_c = new CharTest();
    p_c->setJoystickId(0);
    //p_c->unregisterInterest(df::JOYSTICK_EVENT);
    //p_c->registerInterest(df::KEYBOARD_EVENT);
    // Character *p_c = new ScytheGirl();

    df::Position starting_pos_2(64, 200);
    p_c->setPos(starting_pos_2);
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