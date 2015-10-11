#include "GameOver.h"

GameOver::GameOver(int new_winningPlayer){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::WorldManager &w_m = df::WorldManager::getInstance();
    w_m.setViewFollowing(this);

    winningPlayer = new_winningPlayer;

    df::Sprite *p_temp_sprite = getGameOverSprite();

    setSprite(p_temp_sprite);
    time_to_live = 100;
    setSpriteSlowdown(15); //1/3 speed animation
    setTransparency('#'); //transparent sprite


    time_to_live = p_temp_sprite->getFrameCount() * 300;

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

void GameOver::draw() {
    df::Frame frame = this->getSprite()->getFrame(0);
    int width = frame.getWidth();
    int height = frame.getHeight();

    std::string framestr = frame.getString();

    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char char_to_draw = framestr[i*width + j];
            if (char_to_draw != this->getTransparency()) {
                df::Position temp_pos(1 + j, 1 + i);
                graphics_manager.drawCh(temp_pos, char_to_draw, this->getColor(), true);
            }
        }
    }
}

df::Sprite* GameOver::getGameOverSprite(){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    //Keyboard is only player
    Organizer &p_org = Organizer::getInstance();
    if (p_org.getPlayerNum() <= 1){
        return resource_manager.getSprite("alone");
    }
    //Keyboard is player two
    else{
        switch (winningPlayer){
            default:
                return resource_manager.getSprite("nobodyWins");
            case 0:
                return resource_manager.getSprite("player1Wins");
                break;
            case 1:
                return resource_manager.getSprite("player2Wins");
                break;
            case 2:
                return resource_manager.getSprite("player3Wins");
                break;
            case 3:
                return resource_manager.getSprite("player4Wins");
                break;
            case 4:
                return resource_manager.getSprite("player2Wins");
                break;

        }
    }
}
