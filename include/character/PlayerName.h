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
    df::Position offset;

public:
    PlayerName();
    PlayerName(std::string new_name);
    void draw(void);

    void setName(std::string new_name);
    std::string getName() const;

}
;

#endif