#ifndef __CHARACTERSELECT_H__
#define __CHARACTERSELECT_H__

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

class CharacterSelect : public df::Object {
private:
    int player;
    unsigned int joystickID;

public:
    CharacterSelect();

        //get and set id
    void setPlayer(int new_id);
    int getPlayer() const;

        //get and set character
    void setCharacter(Character *new_player);
    Character getCharacter() const;
    int eventHandler(const df::Event *p_e);


};

#endif