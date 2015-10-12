#include "Platform.h"

Platform::Platform(Stages s){
    // Dragonfly managers needed for this method.
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    
    df::Sprite *p_temp_sprite = NULL;
    // Setup "bullet" sprite.
    switch(s) {
        case ULTIMATE_TERMINAL:
            p_temp_sprite = resource_manager.getSprite("ut-platform");
            break;
        case VORTEX:
            p_temp_sprite = resource_manager.getSprite("vortex-platform");
            break;
        case VACATION:
            p_temp_sprite = resource_manager.getSprite("vacation-platform");
            break;
        default:
            p_temp_sprite = resource_manager.getSprite("ut-platform");
    }
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
    this->setAltitude(0);

    this->setTransparency('#');

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