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

void loadResources();
void startUpGame();
void startStage(Stage *p_s);

int main(int argc, char *argv[]) {
    df::GameManager &game_manager = df::GameManager::getInstance();
    game_manager.startUp();

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    loadResources();
    startUpGame();

    // Run game
    game_manager.run();

    game_manager.shutDown();

    return 0;
}

void loadResources() {

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    // Load sprite
    resource_manager.loadSprite("Sprites/testsprite.txt", "test");
    resource_manager.loadSprite("Sprites/stages/ultimate_terminal.txt", "stage_ut");

}

void startUpGame() {
    // Start up the game stuff
    //Add an organizer to listen for keyboard input (q for quit);
   Organizer &org = Organizer::getInstance();

   //Load the stage;
    Stage *p_s = new UltimateTerminal();
    startStage(p_s);

    Character *p_c = new CharTest();
}

void startStage(Stage *p_s) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();

}
