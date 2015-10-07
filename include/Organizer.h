#ifndef __ORGANIZER_H__
#define __ORGANIZER_H__

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
#include "Selector.h"

class Organizer : public df::Object{
private:
        Organizer(); //Private constructor for singleton
        Organizer(Organizer const&);  //prevents copying
        void operator = (Organizer const&); //prevents 
        bool gameStarted;

        Character *charArray[4];
        Stage *p_stage;
        int characterCount;

public:
    static Organizer &getInstance();
    int eventHandler(const df::Event *p_e);

    void startMatch();
    void startStage(Stage *p_s);

    void Organizer::selectCharacters();

};


#endif