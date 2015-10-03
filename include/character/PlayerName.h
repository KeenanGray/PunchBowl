#ifndef __PLAYERNAME_H__
#define __PLAYERNAME_H__

#include "Object.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "EventStep.h"

class PlayerName : public df::Object{
private:
    std::string name;

public:
    PlayerName();
    PlayerName(std::string new_name);
    void draw(void);
    void updateNamePos(df::Position hero_pos);
};

#endif