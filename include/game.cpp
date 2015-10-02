//Dragonfly Engine Includes
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

//Game includes
#include "Platform.h"
#include "Organizer.h"

void loadResources();
void populateWorld();

int main(int argc, char *argv[]) {
    // Game manager will startup log manager automatically, but
    // I want to startup log_manager with logging level 0. 
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.startUp(0);
    log_manager.setFlush(true);

    df::GameManager &game_manager = df::GameManager::getInstance();
    game_manager.startUp();

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    loadResources();

    //Populate World
    populateWorld();

    // Run game
    game_manager.run();

    game_manager.shutDown();

    return 0;
}

void loadResources(){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    // Load sprite
    resource_manager.loadSprite("Sprites/platform.txt", "platform");
}
void populateWorld(){
    Organizer &org = Organizer::getInstance();
    new Platform();
}