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
void startUpGame();
void startStage(Stage *p_s);

int main(int argc, char *argv[]) {
    df::GameManager &game_manager = df::GameManager::getInstance();
    game_manager.startUp();

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    df::LogManager::getInstance().setFlush(true);

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
    resource_manager.loadSprite("Sprites/platform.txt", "platform");

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
    
    resource_manager.loadSprite("Sprites//alien-spr/alien-right-spr.txt", "alien-right-spr");
    resource_manager.loadSprite("Sprites//alien-spr/alien-right-walk-spr.txt", "alien-right-wspr");
    resource_manager.loadSprite("Sprites//alien-spr/alien-left-spr.txt", "alien-left-spr");
    resource_manager.loadSprite("Sprites//alien-spr/alien-left-walk-spr.txt", "alien-left-wspr");

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

    Platform *p1 = new Platform();
    Platform *p2 = new Platform();

    p1->setPos(df::Position(p_s->getPos().getX() - 45, p_s->getPos().getY() - 9));
    p2->setPos(df::Position(p_s->getPos().getX() + 45, p_s->getPos().getY() - 9));

    world_manager.setView(df::Box(df::Position(0, 0), 35, 35));
    world_manager.setBoundary(df::Box(df::Position(0, 0), p_s->getPos().getX() + 10, p_s->getPos().getY()));

    world_manager.setBoundary(df::Box(df::Position(), p_s->getStageBounds().getHorizontal() + 1, p_s->getStageBounds().getVertical()));
    world_manager.setView(df::Box(df::Position(), 96, 32));
}
