/*
 * PUNCHBOWL
 *
 */

// Dragonfly Engine Includes

// Managers
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "character/CharTest.h"
#include "stage/UltimateTerminal.h"
#include "Organizer.h"
#include "Platform.h"

void loadResources();


int main(int argc, char *argv[]) {
    df::GameManager &game_manager = df::GameManager::getInstance();
    game_manager.startUp();

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::LogManager::getInstance().setFlush(true);
    df::LogManager::getInstance().setLogLevel(-1);
    loadResources();

    Organizer &org = Organizer::getInstance();

    // Run game
    game_manager.run();

    game_manager.shutDown();

    return 0;
}

void loadResources() {

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    // Load sprite
    // resource_manager.loadSprite("Sprites/Title.txt", "Title");
    resource_manager.loadSprite("Sprites/testsprite.txt", "test");
    resource_manager.loadSprite("Sprites/stages/ultimate_terminal.txt", "stage_ut");
    resource_manager.loadSprite("Sprites/platform.txt", "platform");

    //Bull
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-spr.txt", "bull-left-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-spr.txt", "bull-right-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-walk-spr.txt", "bull-left-walk-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-walk-spr.txt", "bull-right-walk-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-dash-spr.txt", "bull-left-dash-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-dash-spr.txt", "bull-right-dash-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-crouch-spr.txt", "bull-left-crouch-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-crouch-spr.txt", "bull-right-crouch-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-crawl-spr.txt", "bull-left-crawl-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-crawl-spr.txt", "bull-right-crawl-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-jump-spr.txt", "bull-left-jump-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-jump-spr.txt", "bull-right-jump-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-air-spr.txt", "bull-left-air-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-air-spr.txt", "bull-right-air-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-roll-spr.txt", "bull-left-roll-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-roll-spr.txt", "bull-right-roll-spr");
    
    //Alien
    resource_manager.loadSprite("Sprites//alien-spr/alien-right-spr.txt", "alien-right-spr");
    resource_manager.loadSprite("Sprites//alien-spr/alien-right-walk-spr.txt", "alien-right-wspr");
    resource_manager.loadSprite("Sprites//alien-spr/alien-left-spr.txt", "alien-left-spr");
    resource_manager.loadSprite("Sprites//alien-spr/alien-left-walk-spr.txt", "alien-left-wspr");
}


