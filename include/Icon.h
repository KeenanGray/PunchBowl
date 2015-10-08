#ifndef __Icon_H__
#define __Icon_H__

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

class Icon : public df::Object {
private:
    Icon(); //icon must be created with name

    std::string name;

public:
    //Constructor for icon with characterName string give
    Icon::Icon(std::string characterName);

    //get and set name
    void setName(int new_name);
    std::string getName() const;

    int eventHandler(const df::Event *p_e);

};

#endif