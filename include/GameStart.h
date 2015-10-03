#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "LogManager.h"

#include "EventKeyboard.h"

#include "GameStart.h"
#include "Saucer.h"s
#include "Hero.h"
#include "Points.h"

GameStart::GameStart(){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::Sprite *p_temp_sprite;

    p_temp_sprite = resource_manager.getSprite("gamestart");
    if (!p_temp_sprite){
        log_manager.writeLog("GameStart::GameStart(): Warning! Sprite '%s' not found", "gamestart");
    }
    else{
        setSprite(p_temp_sprite);
        setSpriteSlowdown(15); //1/3 speed animation
        setTransparency('#'); //transparent sprite

        setLocation(df::CENTER_CENTER);

    }
    setType("GameStart");
    setLocation(df::CENTER_CENTER);

    registerInterest(df::KEYBOARD_EVENT);

    // Play start music.
    p_music = df::ResourceManager::getInstance().getMusic("start music");
    playMusic();

    df::ObjectList object_list = world_manager.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object *p_o = i.currentObject();
        if (p_o->getType() == "Victory")
            world_manager.markForDelete(p_o);
    }
}

int GameStart::eventHandler(const df::Event *p_e) {
    df::GameManager &game_manager = df::GameManager::getInstance();

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
        switch (p_keyboard_event->getKey()) {
            case df::Keyboard::P: 			// play
                start();
                break;
            case df::Keyboard::Q:			// quit
                game_manager.setGameOver();
                break;
            default:
                break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start(){

    setActive(false);
    // Pause start music.
    p_music->pause();
}

void GameStart::draw() {
    df::Object::draw();
}

// Play start music.
void GameStart::playMusic() {
    p_music->play();
}
