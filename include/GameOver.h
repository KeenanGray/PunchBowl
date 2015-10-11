#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "EventStep.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include <stdlib.h>
#include "ViewObject.h"
#include "Organizer.h"
class GameOver : public df::ViewObject {
private:
    GameOver();
    int time_to_live;
    int winningPlayer;
public:
    GameOver(int new_winningPlayer);
    ~GameOver();
    int eventHandler(const df::Event *p_e);
    void step();
    virtual void draw();
    df::Sprite *getGameOverSprite();
};

#endif