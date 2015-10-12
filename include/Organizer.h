#ifndef __ORGANIZER_H__
#define __ORGANIZER_H__

#include <sstream>
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

#include "Clock.h"
#include "utility.h"

// Punchbowl headers
#include "Platform.h"
#include "Selector.h"
#include "Icon.h"
#include "EventDeath.h"
#include "GameOver.h"
#include "StageIcon.h"

//Stages
#include "stage/Stage.h"
#include "stage/UltimateTerminal.h"
#include "stage/Vortex.h"
#include "stage/Vacation.h"
//Characters
#include "character/Character.h"
#include "character/CharTest.h"
#include "character/BullChar.h"
#include "character/ScytheGirlChar.h"
#include "character/RobotChar.h"
#include "character/OctopusChar.h"

#include "LivesDisplay.h"

enum ScreenState {
    UNDEFINED_STATE = -1,
    SPLASH_SCREEN,
    CHARACTER_SCREEN,
    STAGE_SCREEN,
    GAME_SCREEN,
};

class Organizer : public df::Object{
private:
        Organizer(); //Private constructor for singleton
        Organizer(Organizer const&);  //prevents copying
        void operator = (Organizer const&); //prevents 

        ScreenState state;

        bool charactersSelected;
        bool gameOver;

        Characters charArray[5];
        Character *char_obj_array[5];
        LivesDisplay *livesDisplayArray[5];
        
        Icon *bull_icon;
        Icon *robot_icon;
        Icon *sgirl_icon;
        Icon *octopus_icon;

        StageIcon *ut_icon;
        StageIcon *vortex_icon;
        StageIcon *vacation_icon;

        Stage *p_stage;

        //Number of characters selected
        int characterCount;
        //Number of players in the game
        int player_count;

        df::ViewObject *LivesCounter;
        int numberOfLives;
        

public:
    static Organizer &getInstance();
    int eventHandler(const df::Event *p_e);

    void startMatch();
    void startStage();

    void selectCharacters();
    void selectStage();

    Character *getCharacter(Characters character);

    virtual void draw();

    bool getMatchStarted() const;
    ScreenState getState() const;
    int getPlayerNum() const;

    LivesDisplay** getLivesDisplay();
};


#endif