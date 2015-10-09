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
class GameOver : public df::ViewObject {
private:
    int time_to_live;

public:
    GameOver(int winningPlayer);
    ~GameOver();
    int eventHandler(const df::Event *p_e);
    void step();
    virtual void draw();
};

#endif