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
#include "character/ScytheGirlChar.h"
#include "Platform.h"
#include "Icon.h"
#include "SelectedEvent.h"

class Selector : public df::Object {
private:
    unsigned int joystickID;
    int playerID; //Between 1 and 4

    // Passthrough for keyboard controls
    int keyboard(const df::EventKeyboard *p_ke);

    // Whether or not x and y axis events were received
    bool x_axis_received;
    bool y_axis_received;
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