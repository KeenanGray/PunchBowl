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
            df::GameManager &game_manager = df::GameManager::getInstance();
            game_manager.setGameOver();
            return 1;
        }

        if (keyboard_event->getKey() == df::Input::P) {
            world_manager.removeObject(this); //Remove the object from WM so it isn't drawn
            startUpGame();
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

    p1->setPos(df::Position(p_s->getPos().getX() - 45, p_s->getPos().getY() - 9));
    p2->setPos(df::Position(p_s->getPos().getX() + 45, p_s->getPos().getY() - 9));

    world_manager.setView(df::Box(df::Position(0, 0), 35, 35));
    world_manager.setBoundary(df::Box(df::Position(0, 0), p_s->getPos().getX() + 10, p_s->getPos().getY()));

    world_manager.setBoundary(df::Box(df::Position(), p_s->getStageBounds().getHorizontal() + 1, p_s->getStageBounds().getVertical()));
    world_manager.setView(df::Box(df::Position(), 96, 32));
}