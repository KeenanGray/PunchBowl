#include "Organizer.h"

Organizer::Organizer() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Organizer");

    setSolidness(df::SPECTRAL);

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(EVENT_SELECTED);
    registerInterest(EVENT_DEATH);

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

    for (int i = 0; i < 4; i++){
        char_obj_array[i] = NULL;
    }
}

Organizer &Organizer::getInstance(){
    static Organizer *org = new Organizer();
    return *org;
}

int Organizer::eventHandler(const df::Event *p_e) {
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
            } else if (charactersSelected) { //Characters are selected - so start the match
                if (!matchStarted) {
                    startMatch();
                }
                //Game started, characters selected, and match all started, ignore start button; 
                //Characters not selected - ignore start button
                return 1;
            }
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
                }
                else //Game is started 
                {
                    if (charactersSelected) { //Characters are selected - so start the match
                        if (!matchStarted) {
                            startMatch();
                        }
                        //Game started, characters selected, and match all started, ignore start button; 
                        //Characters not selected - ignore start button
                        return 1;
                    }
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

    if (p_e->getType() == EVENT_DEATH) {
        df::InputManager &input_manager = df::InputManager::getInstance();
        df::LogManager &l_m = df::LogManager::getInstance();
        const EventDeath *p_de = static_cast<const EventDeath *> (p_e);
        //Move player back to start
        //set pos back to start
        Character *p_tempChar = char_obj_array[p_de->getPlayerId()];
        df::Position pos(64, 200);
        p_tempChar->setPos(pos);
        //Lose a life
        l_m.writeLog("Player lives = %d", p_tempChar->getLives());
        p_tempChar->setLives(p_tempChar->getLives() - 1);
        l_m.writeLog("Player %d has died has %d lives left", p_de->getPlayerId(), p_tempChar->getLives());
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
    
    //Load the stage;
    p_stage = new UltimateTerminal;
    startStage(p_stage);

    df::Position starting_pos_1(168, 200);
    df::Position starting_pos_2(64, 200);

    int controllerNum = i_m.getJoystickCount();
    //Characters are located at index in array that matches their number. (0-4) 
    for (int i = 0; i < controllerNum; i++){
        //For each character, set the appropriate character class and controller
        Character *p_tempChar;

        //Set to correct character
        p_tempChar = getCharacter(charArray[i]);
        p_tempChar->setLives(3);

        p_tempChar->registerInterest(df::JOYSTICK_EVENT);

        p_tempChar->setJoystickId(i); //Actual joystick ids are 0-4 

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
        this->char_obj_array[i] = p_tempChar;
    }

    // Start a keyboard player (Keyboard player only possible in 1v1 games.
    if (controllerNum < 2) {
        //Keyboard player's character is stored in 4th element of array.
        Character *p_tempChar;

        p_tempChar = getCharacter(charArray[4]);

        //Not a joystick so ID is 4
        p_tempChar->setJoystickId(4);

        p_tempChar->unregisterInterest(df::JOYSTICK_EVENT);
        p_tempChar->registerInterest(df::KEYBOARD_EVENT);

        p_tempChar->setObjectColor(df::MAGENTA);
        p_tempChar->setPos(starting_pos_2);
        this->char_obj_array[4] = p_tempChar;
    }

    matchStarted = true;
}

void Organizer::startStage(Stage *p_s) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    this->setSpriteIndex(2);
    this->setSpriteSlowdown(0);
    this->setAltitude(0);
    this->setPos(world_manager.getView().getPos());

    Platform *p1 = new Platform();
    Platform *p2 = new Platform();

    // world_manager.setView(df::Box(df::Position(0, 0), 35, 35));
    world_manager.setBoundary(df::Box(df::Position(0, 0), p_s->getPos().getX() + 10, p_s->getPos().getY()));

    world_manager.setBoundary(df::Box(df::Position(), p_s->getStageBounds().getHorizontal() + 90, p_s->getStageBounds().getVertical()));
    // world_manager.setView(df::Box(df::Position(), 96, 32));

    p_s->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() - 30));

    p1->setPos(df::Position(p_s->getPos().getX() - 45, p_s->getPos().getY() - 9));
    p2->setPos(df::Position(p_s->getPos().getX() + 45, p_s->getPos().getY() - 9));
}

void Organizer::selectCharacters(){
    df::InputManager &input_manager = df::InputManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    int controllersNum = input_manager.getJoystickCount();
    //Create character selectors for each player
    for (int i = 0; i < controllersNum; i++){
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
    // Start a keyboard player; id is 5
    if (controllersNum < 2) {
        Selector *tmp_sel = new Selector;
        tmp_sel->setPlayerId(4);
        tmp_sel->setJoystickId(4);
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
    
    gameStarted = true;
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

void Organizer::draw() {
    if (matchStarted) {
        df::WorldManager &world_manager = df::WorldManager::getInstance();
        int min_vert = 32766;
        int max_vert = -32766;
        int min_horiz = 32766;
        int max_horiz = -32766;
        for (int i = 0; i < this->characterCount; i++) {
            Character *temp_c = this->char_obj_array[i];
            int temp_x = temp_c->getPos().getX();
            int temp_y = temp_c->getPos().getY();
            if (temp_x > max_horiz) {
                max_horiz = temp_x;
            }
            if (temp_x < min_horiz) {
                min_horiz = temp_x;
            }
            if (temp_y > max_vert) {
                max_vert = temp_y;
            }
            if (temp_y < min_vert) {
                min_vert = temp_y;
            }
        }

        min_vert = std::max(0, min_vert - 24);
        max_vert = std::min(world_manager.getBoundary().getVertical(), max_vert + 24);
        min_horiz = std::max(0, min_horiz - 48);
        max_horiz = std::min(world_manager.getBoundary().getHorizontal(), max_horiz + 48);
        int temp_width = (max_horiz-min_horiz)/3;
        world_manager.setView(df::Box(
            df::Position(min_horiz, (max_vert+min_vert-temp_width)/2), 
            max_horiz-min_horiz, 
            temp_width)
            );
        this->setPos(world_manager.getView().getPos());
    }
    if (!gameStarted) {
        Object::draw();
    }
}