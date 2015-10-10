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
#include "Platform.h"
#include "Selector.h"
#include "Icon.h"
#include "EventDeath.h"
#include "GameOver.h"

//Stages
#include "stage/Stage.h"
#include "stage/UltimateTerminal.h"
//Characters
#include "character/Character.h"
#include "character/CharTest.h"
#include "character/BullChar.h"
#include "character/ScytheGirlChar.h"
#include "character/RobotChar.h"

#include "LivesDisplay.h"

class Organizer : public df::Object{
private:
        Organizer(); //Private constructor for singleton
        Organizer(Organizer const&);  //prevents copying
        void operator = (Organizer const&); //prevents 

        bool gameStarted;
        bool charactersSelected;
        bool matchStarted;

        Characters charArray[5];
        Character *char_obj_array[5];
        LivesDisplay *livesDisplayArray[5];
        
        Icon *bull_icon;
        Icon *robot_icon;
        Icon *sgirl_icon;

        Stage *p_stage;
        //Number of characters selected
        int characterCount;
        //Number of players in the game
        int player_count;
        

public:
    static Organizer &getInstance();
    int eventHandler(const df::Event *p_e);

    void startMatch();
    void startStage(Stage *p_s);

    void selectCharacters();

    Character *getCharacter(Characters character);

    virtual void draw();
};


#endif