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
    resource_manager.loadSprite("Sprites/Title-spr.txt", "Title");
    //Character selector sprite
    resource_manager.loadSprite("Sprites/Selector-spr.txt", "selector");
    resource_manager.loadSprite("Sprites/SelectedObj-spr.txt", "selectedObj");
    
#pragma region CharacterIcons
    resource_manager.loadSprite("Sprites/icons/Characters/Bull-icon.txt", "Bull-icon");
    resource_manager.loadSprite("Sprites/icons/Characters/Robot-icon.txt", "Robot-icon");
    resource_manager.loadSprite("Sprites/icons/Characters/Scythe-icon.txt", "ScytheGirl-icon");
    resource_manager.loadSprite("Sprites/icons/Characters/Octopus-icon.txt", "Octopus-icon");

    resource_manager.loadSprite("Sprites/icons/Stages/UT_icon.txt", "UT-icon");
    resource_manager.loadSprite("Sprites/icons/Stages/Vortex_icon.txt", "Vortex-icon");
    resource_manager.loadSprite("Sprites/icons/Stages/Vacation_icon.txt", "Vacation-icon");

#pragma endregion
    resource_manager.loadSprite("Sprites/testsprite.txt", "test");
    resource_manager.loadSprite("Sprites/stages/ultimate_terminal.txt", "stage_ut");
    resource_manager.loadSprite("Sprites/stages/ut-platform-spr.txt", "ut-platform");

    resource_manager.loadSprite("Sprites/stages/vortex.txt", "stage_vortex");
    resource_manager.loadSprite("Sprites/stages/vortex-platform-spr.txt", "vortex-platform");

    resource_manager.loadSprite("Sprites/stages/vacation.txt", "stage_vacation");
    resource_manager.loadSprite("Sprites/stages/vacation-platform-spr.txt", "vacation-platform");

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
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-attack-down-spr.txt", "bull-left-atk-down-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-attack-down-spr.txt", "bull-right-atk-down-spr");

    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-air-neutral-spr.txt", "bull-left-air-neutral-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-air-neutral-spr.txt", "bull-right-air-neutral-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-air-up-spr.txt", "bull-left-air-up-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-air-up-spr.txt", "bull-right-air-up-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-air-down-spr.txt", "bull-left-air-down-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-air-down-spr.txt", "bull-right-air-down-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-air-back-spr.txt", "bull-left-air-back-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-air-back-spr.txt", "bull-right-air-back-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-left-recovery-spr.txt", "bull-left-recovery-spr");
    resource_manager.loadSprite("Sprites/bull-spr/attack/bull-right-recovery-spr.txt", "bull-right-recovery-spr");
#pragma endregion

#pragma region LoadScytheGirl
    // Scythe Girl
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-spr.txt", "sg-left-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-spr.txt", "sg-right-spr");
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
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-left-stunned-spr.txt", "sg-left-stunned-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/move/scythe-girl-right-stunned-spr.txt", "sg-right-stunned-spr");

    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-attack-neutral-spr.txt", "sg-left-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-attack-neutral-spr.txt", "sg-right-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-attack-side-spr.txt", "sg-left-atk-side-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-attack-side-spr.txt", "sg-right-atk-side-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-attack-up-spr.txt", "sg-left-atk-up-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-attack-up-spr.txt", "sg-right-atk-up-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-attack-down-spr.txt", "sg-left-atk-down-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-attack-down-spr.txt", "sg-right-atk-down-spr");

    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-air-neutral-spr.txt", "sg-left-air-neutral-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-air-neutral-spr.txt", "sg-right-air-neutral-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-air-up-spr.txt", "sg-left-air-up-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-air-up-spr.txt", "sg-right-air-up-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-air-down-spr.txt", "sg-left-air-down-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-air-down-spr.txt", "sg-right-air-down-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-air-back-spr.txt", "sg-left-air-back-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-air-back-spr.txt", "sg-right-air-back-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-left-recovery-spr.txt", "sg-left-recovery-spr");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/attack/scythe-girl-right-recovery-spr.txt", "sg-right-recovery-spr");

    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-0-ccw.txt", "scythe-0-ccw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-0-cw.txt", "scythe-0-cw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-90-ccw.txt", "scythe-90-ccw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-90-cw.txt", "scythe-90-cw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-180-ccw.txt", "scythe-180-ccw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-180-cw.txt", "scythe-180-cw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-270-ccw.txt", "scythe-270-ccw");
    resource_manager.loadSprite("Sprites/scythe-girl-spr/scythe/scythe-270-cw.txt", "scythe-270-cw");
#pragma endregion

#pragma region loadRobotSprites
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
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-attack-down-spr.txt", "robot-left-atk-down-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-attack-down-spr.txt", "robot-right-atk-down-spr");

    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-air-neutral-spr.txt", "robot-left-air-neutral-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-air-neutral-spr.txt", "robot-right-air-neutral-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-air-up-spr.txt", "robot-left-air-up-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-air-up-spr.txt", "robot-right-air-up-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-air-down-spr.txt", "robot-left-air-down-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-air-down-spr.txt", "robot-right-air-down-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-air-back-spr.txt", "robot-left-air-back-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-air-back-spr.txt", "robot-right-air-back-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-left-recovery-spr.txt", "robot-left-recovery-spr");
    resource_manager.loadSprite("Sprites/robot-spr/attack/robot-right-recovery-spr.txt", "robot-right-recovery-spr");
#pragma endregion

#pragma region loadOctopusSprites
    //Octopus
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-spr.txt", "octopus-left-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-spr.txt", "octopus-right-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-walk-spr.txt", "octopus-left-walk-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-walk-spr.txt", "octopus-right-walk-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-dash-spr.txt", "octopus-left-dash-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-dash-spr.txt", "octopus-right-dash-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-crouch-spr.txt", "octopus-left-crouch-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-crouch-spr.txt", "octopus-right-crouch-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-crawl-spr.txt", "octopus-left-crawl-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-crawl-spr.txt", "octopus-right-crawl-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-jump-spr.txt", "octopus-left-jump-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-jump-spr.txt", "octopus-right-jump-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-air-spr.txt", "octopus-left-air-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-air-spr.txt", "octopus-right-air-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-roll-spr.txt", "octopus-left-roll-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-roll-spr.txt", "octopus-right-roll-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-dodge-spr.txt", "octopus-left-dodge-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-dodge-spr.txt", "octopus-right-dodge-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-fall-spr.txt", "octopus-left-fall-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-fall-spr.txt", "octopus-right-fall-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-left-stunned-spr.txt", "octopus-left-stunned-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/move/octopus-right-stunned-spr.txt", "octopus-right-stunned-spr");

    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-attack-neutral-spr.txt", "octopus-left-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-attack-neutral-spr.txt", "octopus-right-atk-neutral-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-attack-side-spr.txt", "octopus-left-atk-side-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-attack-side-spr.txt", "octopus-right-atk-side-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-attack-up-spr.txt", "octopus-left-atk-up-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-attack-up-spr.txt", "octopus-right-atk-up-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-attack-down-spr.txt", "octopus-left-atk-down-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-attack-down-spr.txt", "octopus-right-atk-down-spr");

    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-air-neutral-spr.txt", "octopus-left-air-neutral-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-air-neutral-spr.txt", "octopus-right-air-neutral-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-air-up-spr.txt", "octopus-left-air-up-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-air-up-spr.txt", "octopus-right-air-up-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-air-down-spr.txt", "octopus-left-air-down-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-air-down-spr.txt", "octopus-right-air-down-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-air-back-spr.txt", "octopus-left-air-back-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-air-back-spr.txt", "octopus-right-air-back-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-left-recovery-spr.txt", "octopus-left-recovery-spr");
    resource_manager.loadSprite("Sprites/octopus-spr/attack/octopus-right-recovery-spr.txt", "octopus-right-recovery-spr");
#pragma endregion


    resource_manager.loadSprite("Sprites/gameOver/player1Wins.txt", "player1Wins");
    resource_manager.loadSprite("Sprites/gameOver/player2Wins.txt", "player2Wins");
    resource_manager.loadSprite("Sprites/gameOver/player3Wins.txt", "player3Wins");
    resource_manager.loadSprite("Sprites/gameOver/player4Wins.txt", "player4Wins");
    resource_manager.loadSprite("Sprites/gameOver/nobodyWins.txt", "nobodyWins");
    resource_manager.loadSprite("Sprites/gameOver/alone.txt", "alone");




    // Sounds
    resource_manager.loadSound("Music/hits/hit1.wav", "hit1");
    resource_manager.loadSound("Music/hits/hit2.wav", "hit2");
    resource_manager.loadSound("Music/hits/hit3.wav", "hit3");
    resource_manager.loadSound("Music/hits/heavy_hit1.wav", "heavy1");
    resource_manager.loadSound("Music/hits/heavy_hit2.wav", "heavy2");
    resource_manager.loadSound("Music/jump/jump1.wav", "jump1");
    resource_manager.loadSound("Music/jump/jump2.wav", "jump2");
    resource_manager.loadSound("Music/jump/jump3.wav", "jump3");
    resource_manager.loadSound("Music/jump/jump4.wav", "jump4");
    resource_manager.loadSound("Music/jump/jump5.wav", "jump5");
    resource_manager.loadSound("Music/other/death.wav", "death");
    resource_manager.loadSound("Music/other/dodge.wav", "dodge");
    resource_manager.loadSound("Music/other/roll.wav", "roll");

    resource_manager.loadMusic("Music/soundtrack/main_theme.wav", "main");
    resource_manager.loadMusic("Music/soundtrack/combat1.wav", "combat1");
    resource_manager.loadMusic("Music/soundtrack/combat2.wav", "combat2");
    resource_manager.loadMusic("Music/soundtrack/combat3.wav", "combat3");



}


