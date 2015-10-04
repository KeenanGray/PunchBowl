#include "Organizer.h"

Organizer::Organizer(){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

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
    return 0;
}

void Organizer::startUpGame() {
    // Start up the game stuff
    //Add an organizer to listen for keyboard input (q for quit);
    Organizer &org = Organizer::getInstance();

    //Load the stage;
    Stage *p_s = new UltimateTerminal();
    startStage(p_s);

    Character *p_c = new CharTest();
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