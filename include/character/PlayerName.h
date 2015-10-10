#ifndef __PLAYERNAME_H__
#define __PLAYERNAME_H__

#include "Object.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "EventStep.h"

#include "Character.h"

class Character;

class PlayerName : public df::Object{
private:
    std::string name;
    df::Position offset;
    Character *player;

public:
    PlayerName();
    PlayerName(std::string new_name, Character *init_player);
    void draw(void);

    void setName(std::string new_name);
    std::string getName() const;

    void updatePosition();

};

#endif