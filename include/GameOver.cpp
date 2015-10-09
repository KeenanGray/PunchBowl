#include "GameOver.h"

GameOver::GameOver(int winningPlayer){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::WorldManager &w_m = df::WorldManager::getInstance();
    w_m.setViewFollowing(this);
    //Set to player1 as default
    df::Sprite *p_temp_sprite = resource_manager.getSprite("player1Wins");

    switch (winningPlayer){
        case 0:
            p_temp_sprite = resource_manager.getSprite("player1Wins");
            break;
        case 1:
            p_temp_sprite = resource_manager.getSprite("player2Wins");
            break;
        case 2:
            p_temp_sprite = resource_manager.getSprite("player3Wins");
            break;
        case 3:
            p_temp_sprite = resource_manager.getSprite("player4Wins");
        case 4:
            p_temp_sprite = resource_manager.getSprite("player1Wins");
            break;
    }
    setSprite(p_temp_sprite);
    time_to_live = 100;
    setSpriteSlowdown(15); //1/3 speed animation
    setTransparency('#'); //transparent sprite


    time_to_live = p_temp_sprite->getFrameCount() * 15;

    setLocation(df::CENTER_CENTER);

    registerInterest(df::STEP_EVENT);
}

GameOver::~GameOver(){
    df::GameManager &g_m = df::GameManager::getInstance();
    g_m.setGameOver(true); //end the game.
}

int GameOver::eventHandler(const df::Event *p_e){
    if (p_e->getType() == df::STEP_EVENT){
        step();
        return 1;
    }
    return 0;
}

// Count down to end of message.
void GameOver::step() {
    time_to_live--;
    if (time_to_live <= 0) {
        df::WorldManager &world_manager = df::WorldManager::getInstance();
        world_manager.markForDelete(this);
    }
}
