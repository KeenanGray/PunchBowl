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
#include "character/Character.h"
#include "character/CharTest.h"
#include "character/ScytheGirlChar.h"

enum Characters
{
    NONE,
    BULL,
    SGIRL,
    ROBOT,
    OCTOPUS
};

class Icon : public df::Object {
private:
    Icon(); //icon must be created with name

    Characters iconChar;
    //Name used to load sprite
    std::string name;

public:
    //Constructor for icon with characterName string give
    Icon(Characters new_iconChar, std::string new_name);

    //get and set iconChar
    void setIconChar(Characters new_iconChar);
    Characters getIconChar() const;

    virtual void draw();
};

#endif