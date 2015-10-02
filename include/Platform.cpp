#include "Platform.h"

Platform::Platform(){
    // Dragonfly managers needed for this method.
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    // Setup "bullet" sprite.
    df::Sprite *p_temp_sprite = resource_manager.getSprite("platform");
    if (!p_temp_sprite) {
        log_manager.writeLog("Platform::Platform(): Warning! Sprite '%s' not found",
            "platform");
    }
    else {
        setSprite(p_temp_sprite);
    }

    // Set object type.
    setType("Platform");
    setSolidness(df::SOFT);

    setPos(df::Position(20, 10));

    setSpriteSlowdown(10);

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
}

Platform::~Platform(){

}

int Platform::eventHandler(const df::Event *p_e){
    return 0;
}