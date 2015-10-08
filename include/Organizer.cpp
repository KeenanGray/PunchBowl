#include "Organizer.h"

Organizer::Organizer(){
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Organizer");

    setSolidness(df::SPECTRAL);

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    registerInterest(EVENT_SELECTED);


    df::Sprite *tmp_spr = resource_manager.getSprite("Title");
    setSprite(tmp_spr);
    setSpriteSlowdown(25);

    world_manager.setView(df::Box(df::Position(), tmp_spr->getWidth() + 10, tmp_spr->getHeight() + 10));
    world_manager.setBoundary(df::Box(df::Position(), tmp_spr->getWidth() + 10, tmp_spr->getHeight() + 10));

    setPos(df::Position(world_manager.getView().getHorizontal() / 2, world_manager.getView().getVertical() / 2));

    gameStarted = false;
    charactersSelected = false;
    matchStarted = false;

    //character count = 0;
    characterCount = 0;
    this->player_count = 0;
    //No characters selected
}

Organizer &Organizer::getInstance(){
    static Organizer *org = new Organizer();
    return *org;
}

int Organizer::eventHandler(const df::Event *p_e){
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *keyboard_event = static_cast<const df::EventKeyboard *> (p_e);
        if (keyboard_event->getKey() == df::Input::Q) {
            if (!gameStarted){
                df::GameManager &game_manager = df::GameManager::getInstance();
                game_manager.setGameOver();
                return 1;
            }
            else{
                df::GameManager &game_manager = df::GameManager::getInstance();
                game_manager.setGameOver();
                return 1;
            }
        }

        if (keyboard_event->getKey() == df::Input::P) {
            if (!gameStarted) {
                selectCharacters();
                gameStarted = true;
            } else if (charactersSelected) { //Characters are selected - so start the match
                if (!matchStarted) {
                    startMatch();
                } else {
                    return 1; //Game started, characters selected, and match all started, ignore start button; 
                }
            } else { //Characters not selected - ignore start button
                return 1;
            }
            return 1;
        }
    }
    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN) {
            if (p_je->getButton() == 7) {
                // Start Button
                if (!gameStarted)  //Go from title screen to character select screen
                {
                    selectCharacters();
                    gameStarted = true;
                }
                else //Game is started 
                {
                    if (charactersSelected) //Characters are selected - so start the match

                        if (!matchStarted)
                            startMatch();
                        else
                            return 1; //Game started, characters selected, and match all started, ignore start button; 

                        else //Characters not selected - ignore start button
                            return 1;
                }
            }

            if (p_je->getButton() == 6) {
                // Back Button
                if (!gameStarted){
                    df::GameManager &game_manager = df::GameManager::getInstance();
                    game_manager.setGameOver();
                    return 1;
                }
                else{
                    df::GameManager &game_manager = df::GameManager::getInstance();
                    game_manager.setGameOver();
                    return 1;
                }
            }
        }
    }

    //When a character is selected
    if (p_e->getType() == EVENT_SELECTED) {
        df::InputManager &input_manager = df::InputManager::getInstance();
        df::LogManager &l_m = df::LogManager::getInstance();
        const SelectedEvent *p_se = static_cast<const SelectedEvent *> (p_e);
        l_m.writeLog(3, "Event_Selected Event recieved with char = %d", p_se->getSelectedChar());
        characterCount += 1;
        if (characterCount == this->player_count){
            charactersSelected = true;
        }

        //Assign characters to array
        switch (p_se->getSelectedChar())
        {
            case BULL:
                charArray[p_se->getSelectedPlayerId()] = p_se->getSelectedChar();
                break;
            case ROBOT:
                charArray[p_se->getSelectedPlayerId()] = p_se->getSelectedChar();
                break;
            default:
                break;
        }


        return 1;
    }
    return 0;
}

void Organizer::startMatch() {
    //Get inputmanager to get number of joysticks connected
    df::InputManager &i_m = df::InputManager::getInstance();
    df::LogManager &l_m = df::LogManager::getInstance();
    l_m.writeLog("match starting");
    // Start up the match, at stage, with character 1 and character 2
    //Add an organizer to listen for keyboard input (q for quit);
    Organizer &org = Organizer::getInstance();

    //Load the stage;
    p_stage = new UltimateTerminal;
    startStage(p_stage);

    df::Position starting_pos_1(168, 200);
    df::Position starting_pos_2(64, 200);

    int playersNum = i_m.getJoystickCount();
    for (int i = 0; i < playersNum; i++){
        //For each character, set the appropriate character class and controller
        Character *p_tempChar;

        p_tempChar = getCharacter(charArray[i]);

        p_tempChar->registerInterest(df::JOYSTICK_EVENT);
        p_tempChar->setJoystickId(i);

        //    df::Position starting_pos_3(168, 200);
        //    df::Position starting_pos_4(168, 200);

        //Set starting positions and colors
        switch (i){
            case 0:
                p_tempChar->setObjectColor(df::RED);
                p_tempChar->setPos(starting_pos_1);
                break;
            case 1:
                p_tempChar->setObjectColor(df::GREEN);
                p_tempChar->setPos(starting_pos_2);
                break;
            case 2:
                p_tempChar->setObjectColor(df::YELLOW);
                p_tempChar->setPos(starting_pos_1);
                break;
            case 3:
                p_tempChar->setObjectColor(df::BLUE);
                p_tempChar->setPos(starting_pos_2);
                break;
        }
    }
    
    // Start a keyboard player
    if (playersNum < 2) {
        //For each character, set the appropriate character class and controller
        Character *p_tempChar;

        p_tempChar = getCharacter(charArray[playersNum]);

        p_tempChar->setJoystickId(1024);
    
        p_tempChar->unregisterInterest(df::JOYSTICK_EVENT);
        p_tempChar->registerInterest(df::KEYBOARD_EVENT);

        p_tempChar->setObjectColor(df::MAGENTA);
        p_tempChar->setPos(starting_pos_2);
    }

    matchStarted = true;
}

void Organizer::startStage(Stage *p_s) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    Platform *p1 = new Platform();
    Platform *p2 = new Platform();

    world_manager.setView(df::Box(df::Position(0, 0), 35, 35));
    world_manager.setBoundary(df::Box(df::Position(0, 0), p_s->getPos().getX() + 10, p_s->getPos().getY()));

    world_manager.setBoundary(df::Box(df::Position(), p_s->getStageBounds().getHorizontal() + 90, p_s->getStageBounds().getVertical()));
    world_manager.setView(df::Box(df::Position(), 96, 32));

    p_s->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() - 30));

    p1->setPos(df::Position(p_s->getPos().getX() - 45, p_s->getPos().getY() - 9));
    p2->setPos(df::Position(p_s->getPos().getX() + 45, p_s->getPos().getY() - 9));
}

void Organizer::selectCharacters(){
    df::InputManager &input_manager = df::InputManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    //Set sprite to blank
    setSpriteIndex(2);
    setSpriteSlowdown(0);
    setAltitude(0);

    int playersNum = input_manager.getJoystickCount();
    //Create character selectors for each player
    for (int i = 0; i < playersNum; i++){
        Selector *tmp_sel = new Selector;
        tmp_sel->setPlayerId(i);
        tmp_sel->setJoystickId(input_manager.getJoysticks()[i]);
        tmp_sel->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 2));

        switch (i){
            case 0:
                tmp_sel->setObjectColor(df::RED);
                break;
            case 1:
                tmp_sel->setObjectColor(df::GREEN);
                break;
            case 2:
                tmp_sel->setObjectColor(df::YELLOW);
                break;
            case 3:
                tmp_sel->setObjectColor(df::BLUE);
                break;
        }
        this->player_count++;
    }
    // Start a keyboard player
    if (playersNum < 2) {
        Selector *tmp_sel = new Selector;
        tmp_sel->setPlayerId(playersNum);
        tmp_sel->setJoystickId(1024);
        tmp_sel->unregisterInterest(df::JOYSTICK_EVENT);
        tmp_sel->registerInterest(df::KEYBOARD_EVENT);
        tmp_sel->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 2));

        tmp_sel->setObjectColor(df::MAGENTA);
        this->player_count++;
    }

    //Create an icon for each of the characters
    Icon *char1 = new Icon(BULL, "Bull");
    Icon *char2 = new Icon(ROBOT, "Robot");
    char1->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 4, world_manager.getBoundary().getVertical() / 4));
    char2->setPos(df::Position(world_manager.getBoundary().getHorizontal() * 3 / 4, world_manager.getBoundary().getVertical() / 4));

}

Character *Organizer::getCharacter(Characters character){
    switch (character){
        case BULL:
            return new BullChar();
            break;
        case ROBOT:
            return new RobotChar();
            break;
        default:
            break;
    }
}