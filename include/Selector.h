#ifndef __Selector_H__
#define __Selector_H__

// Dragonfly Engine headers
// Events
#include "EventKeyboard.h"
#include "EventOut.h"
#include "EventStep.h"
// Managers
#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

#include "utility.h"

// Punchbowl headers
#include "stage/UltimateTerminal.h"
#include "Platform.h"
#include "stage/Stage.h"
#include "stage/UltimateTerminal.h"
#include "character/Character.h"
#include "character/CharTest.h"
#include "character/ScytheGirl.h"
#include "Platform.h"
#include "Icon.h"
#include "SelectedEvent.h"

class Selector : public df::Object {
private:
    unsigned int joystickID;
    int playerID; //Between 1 and 4
public:
    Selector();

    //get and set joyStick
    void setJoystickId(int new_id);
    int getJoystickId() const;

    //get and set playerId
    void setPlayerId(int new_id);
    int getPlayerId() const;

    int eventHandler(const df::Event *p_e);


};

#endif