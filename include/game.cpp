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
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.setLogLevel(2);
    log_manager.setFlush(true);

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    loadResources();

    Organizer &org = Organizer::getInstance();

    // Run game
    game_manager.run();

    game_manager.shutDown();

    return 0;
}

void loadResources() {

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    //Title screen sprite
    resource_manager.loadSprite("Sprites/Title.txt", "Title");
    //Character selector sprite
    resource_manager.loadSprite("Sprites/Select-spr.txt", "selector");
    
#pragma region CharacterIcons
    resource_manager.loadSprite("Sprites/icons/Bull-icon.txt", "Bull-icon");
#pragma endregion
    resource_manager.loadSprite("Sprites/testsprite.txt", "test");
    resource_manager.loadSprite("Sprites/stages/ultimate_terminal.txt", "stage_ut");
    resource_manager.loadSprite("Sprites/platform.txt", "platform");

#pragma region LoadBullSprite
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
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-dodge-spr.txt", "bull-left-dodge-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-dodge-spr.txt", "bull-right-dodge-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-fall-spr.txt", "bull-left-fall-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-fall-spr.txt", "bull-right-fall-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-left-stunned-spr.txt", "bull-left-stunned-spr");
    resource_manager.loadSprite("Sprites/bull-spr/move/bull-right-stunned-spr.txt", "bull-right-stunned-spr");



    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-attack-neutral-spr.txt", "bull-left-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-attack-neutral-spr.txt", "bull-right-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-attack-side-spr.txt", "bull-left-atk-side-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-attack-side-spr.txt", "bull-right-atk-side-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-attack-up-spr.txt", "bull-left-atk-up-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-attack-up-spr.txt", "bull-right-atk-up-spr");
#pragma endregion

#pragma region LoadScytheGirl
    // Scythe Girl
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-spr.txt", "sg-left-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-spr.txt", "sg-right-spr");
    /*
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-walk-spr.txt", "sg-left-walk-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-walk-spr.txt", "sg-right-walk-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-dash-spr.txt", "sg-left-dash-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-dash-spr.txt", "sg-right-dash-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-crouch-spr.txt", "sg-left-crouch-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-crouch-spr.txt", "sg-right-crouch-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-crawl-spr.txt", "sg-left-crawl-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-crawl-spr.txt", "sg-right-crawl-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-jump-spr.txt", "sg-left-jump-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-jump-spr.txt", "sg-right-jump-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-air-spr.txt", "sg-left-air-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-air-spr.txt", "sg-right-air-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-roll-spr.txt", "sg-left-roll-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-roll-spr.txt", "sg-right-roll-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-dodge-spr.txt", "sg-left-dodge-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-dodge-spr.txt", "sg-right-dodge-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-fall-spr.txt", "sg-left-fall-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-fall-spr.txt", "sg-right-fall-spr");
    */
#pragma endregion

#pragma region
    //Robot
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-spr.txt", "robot-left-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-spr.txt", "robot-right-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-walk-spr.txt", "robot-left-walk-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-walk-spr.txt", "robot-right-walk-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-dash-spr.txt", "robot-left-dash-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-dash-spr.txt", "robot-right-dash-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-crouch-spr.txt", "robot-left-crouch-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-crouch-spr.txt", "robot-right-crouch-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-crawl-spr.txt", "robot-left-crawl-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-crawl-spr.txt", "robot-right-crawl-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-jump-spr.txt", "robot-left-jump-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-jump-spr.txt", "robot-right-jump-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-air-spr.txt", "robot-left-air-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-air-spr.txt", "robot-right-air-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-roll-spr.txt", "robot-left-roll-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-roll-spr.txt", "robot-right-roll-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-dodge-spr.txt", "robot-left-dodge-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-dodge-spr.txt", "robot-right-dodge-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-fall-spr.txt", "robot-left-fall-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-fall-spr.txt", "robot-right-fall-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-left-stunned-spr.txt", "robot-left-stunned-spr");
    resource_manager.loadSprite("Sprites/robot-spr/move/robot-right-stunned-spr.txt", "robot-right-stunned-spr");


    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-attack-neutral-spr.txt", "robot-left-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-attack-neutral-spr.txt", "robot-right-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-attack-side-spr.txt", "robot-left-atk-side-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-attack-side-spr.txt", "robot-right-atk-side-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-attack-up-spr.txt", "robot-left-atk-up-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-attack-up-spr.txt", "robot-right-atk-up-spr");
#pragma endregion


}


