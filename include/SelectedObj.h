#ifndef __selectedObj_H__
#define __selectedObj_H__

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
#include "Selector.h"
#include "Organizer.h"

class SelectedObj : public df::Object {
private:
    SelectedObj();
    unsigned int joystickID;

    // Passthrough for keyboard controls
    int keyboard(const df::EventKeyboard *p_ke);

public:
    SelectedObj(int new_playerId);

    int eventHandler(const df::Event *p_e);
};

#endif