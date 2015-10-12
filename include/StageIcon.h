#ifndef __STAGE_ICON_H__
#define __STAGE_ICON_H__

// Dragonfly Engine headers
// Events
#include "EventKeyboard.h"
#include "EventOut.h"
#include "EventStep.h"
// Managers
#include "GraphicsManager.h"
#include "ResourceManager.h"

// Punchbowl headers
#include "stage/UltimateTerminal.h"
#include "Platform.h"
#include "stage/Stage.h"

class StageIcon : public df::Object {
private:
    StageIcon(); //icon must be created with name

    Stages iconStage;
    //Name used to load sprite
    std::string name;

public:
    //Constructor for icon with characterName string give
    StageIcon(Stages new_iconStage, std::string new_name);

    //get and set iconChar
    void setIconStage(Stages new_iconChar);
    Stages getIconStage() const;

    virtual void draw();
};

#endif // __STAGE_ICON_H__