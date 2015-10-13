#include "Organizer.h"

Organizer::Organizer() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Organizer");

    setSolidness(df::SPECTRAL);
    setAltitude(0);
    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(EVENT_SELECTED);
    registerInterest(EVENT_DEATH);

    df::Sprite *tmp_spr = resource_manager.getSprite("Title");
    setSprite(tmp_spr);
    setSpriteSlowdown(25);

    world_manager.setView(df::Box(df::Position(), tmp_spr->getWidth() + 42, tmp_spr->getHeight() + 10));
    world_manager.setBoundary(df::Box(df::Position(), tmp_spr->getWidth() + 42, tmp_spr->getHeight() + 10));

    setPos(df::Position(world_manager.getView().getHorizontal() / 2, world_manager.getView().getVertical() / 2));

    this->gameOver = false;
    this->state = SPLASH_SCREEN;

    //character count = 0;
    characterCount = 0;
    this->player_count = 0;
    //No characters selected

    for (int i = 0; i < 5; i++){
        char_obj_array[i] = NULL;
    }

    numberOfLives = 3;
    LivesCounter = new df::ViewObject(false, df::CENTER_CENTER, df::Color::WHITE);
    LivesCounter->setValue(numberOfLives);
    LivesCounter->setAltitude(df::MAX_ALTITUDE);
    LivesCounter->setViewString("");
    LivesCounter->setPos(df::Position(16, 18));

    df::ResourceManager::getInstance().getMusic("main")->play(true);
}

Organizer &Organizer::getInstance(){
    static Organizer *org = new Organizer();
    return *org;
}

int Organizer::eventHandler(const df::Event *p_e) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *keyboard_event = static_cast<const df::EventKeyboard *> (p_e);
        if (keyboard_event->getAction() == df::KEY_PRESSED) {
            if (keyboard_event->getKey() == df::Input::Q) {
                df::GameManager &game_manager = df::GameManager::getInstance();
                game_manager.setGameOver();
                return 1;
            }

            if (keyboard_event->getKey() == df::Input::P) {
                switch (this->state) {
                    case SPLASH_SCREEN:
                        this->selectCharacters();
                        return 1;
                    case CHARACTER_SCREEN:
                        if (this->charactersSelected) {
                            this->selectStage();
                        }
                        return 1;
                    default:
                        return 0;
                }
            }
            if (keyboard_event->getKey() == df::Input::I) {
                if (keyboard_event->getAction() == df::KEY_PRESSED){
                    // Increase lives
                    if (this->state == SPLASH_SCREEN){
                        if (numberOfLives < 15){
                            numberOfLives++;
                            LivesCounter->setValue(numberOfLives);
                        }
                    }
                }
            }

            if (keyboard_event->getKey() == df::Input::K) {
                if (keyboard_event->getAction() == df::KEY_PRESSED){
                    // Decrease Lives
                    if (this->state == SPLASH_SCREEN){
                        if (numberOfLives > 1){
                            numberOfLives--;
                            LivesCounter->setValue(numberOfLives);
                        }
                    }
                }
            }
        }
    }

    if (p_e->getType() == df::JOYSTICK_EVENT) {
        const df::EventJoystick *p_je = static_cast<const df::EventJoystick *> (p_e);
        if (p_je->getAction() == df::JOYSTICK_BUTTON_DOWN) {
            if (p_je->getButton() == 7) {
                switch (this->state) {
                    case SPLASH_SCREEN:
                        this->selectCharacters();
                        return 1;
                    case CHARACTER_SCREEN:
                        if (this->charactersSelected) {
                            this->selectStage();
                        }
                        return 1;
                    default:
                        return 0;
                }
            }
        }

        if (p_je->getButton() == 3) {
            // Y button
            if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED){
                // Increase lives
                if (this->state == SPLASH_SCREEN){
                    if (numberOfLives < 15){
                        numberOfLives++;
                        LivesCounter->setValue(numberOfLives);
                    }
                }
            }
        }

        if (p_je->getButton() == 0) {
            //A button
            if (p_je->getAction() == df::JOYSTICK_BUTTON_PRESSED){
                // Decrease Lives
                if (this->state == SPLASH_SCREEN){
                    if (numberOfLives > 1){
                        numberOfLives--;
                        LivesCounter->setValue(numberOfLives);
                    }
                }
            }
        }
    }

    //When a character is selected
    if (p_e->getType() == EVENT_SELECTED) {
        const SelectedEvent *p_se = static_cast<const SelectedEvent *> (p_e);
        if (p_se->isCharacter()) {
            df::InputManager &input_manager = df::InputManager::getInstance();
            df::LogManager &l_m = df::LogManager::getInstance();
            l_m.writeLog(3, "Event_Selected Event recieved with char = %d", p_se->getSelectedChar());
            l_m.writeLog(3, "Player count = %d : CharacterCount = %d", player_count, characterCount);
            //Assign characters to array
            if (p_se->getSelectedChar() == NONE)
            {
                characterCount--;
                charArray[p_se->getSelectedPlayerId()] = p_se->getSelectedChar();
            }
            else{
                    characterCount++;
                    charArray[p_se->getSelectedPlayerId()] = p_se->getSelectedChar();
            }

            df::Sound *p_sound = df::ResourceManager::getInstance().getSound("blip");
            p_sound->play();

            if (characterCount == this->player_count){
                charactersSelected = true;
            }
            else
                charactersSelected = false;
        } else {
            df::ResourceManager::getInstance().getMusic("main")->stop();
            switch(p_se->getSelectedStage()) {
                case ULTIMATE_TERMINAL:
                    df::ResourceManager::getInstance().getMusic("combat1")->play(true);
                    this->p_stage = new UltimateTerminal;
                    break;
                case VORTEX:
                    df::ResourceManager::getInstance().getMusic("combat1")->play(true);
                    this->p_stage = new Vortex;
                    break;
                case VACATION:
                    df::ResourceManager::getInstance().getMusic("combat2")->play(true);
                    this->p_stage = new Vacation;
                    break;
                default:
                    df::ResourceManager::getInstance().getMusic("combat1")->play(true);
                    this->p_stage = new UltimateTerminal;
                    break;
            }
            this->startMatch();
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
        LivesDisplay *p_tmpLD = livesDisplayArray[p_de->getPlayerId()];

        df::WorldManager &world_manager = df::WorldManager::getInstance();
        p_tempChar->setPos(this->p_stage->getRespawnPosition());
        p_tempChar->setXVelocity(0);
        p_tempChar->setYVelocity(0);
        p_tempChar->setDamage(0);
        p_tempChar->setFalling(false);
        //Lose a life
        // l_m.writeLog("Player lives = %d", p_tempChar->getLives());
        p_tempChar->setLives(p_tempChar->getLives() - 1);
        p_tmpLD->setValue(p_tempChar->getLives());

        if (p_tempChar->getLives() <= 0){
            world_manager.markForDelete(p_tempChar);
            char_obj_array[p_de->getPlayerId()] = NULL;

            characterCount--;
            if (characterCount <= 1){
                if (!gameOver){
                    //Do end game stuff
                    int winPlayer = -1;
                    for (int i = 0; i < 5; i++){
                        if (char_obj_array[i] != NULL){
                            char_obj_array[i]->setXVelocity(0);
                            char_obj_array[i]->setYVelocity(0);
                            char_obj_array[i]->setPos(this->p_stage->getRespawnPosition());
                            winPlayer = i;
                        }
                    }
                    new GameOver(winPlayer);
                    gameOver = true;
                }
            }
        }
        // l_m.writeLog("Player %d has died has %d lives left", p_de->getPlayerId(), p_tempChar->getLives());
        l_m.writeLog("Player %d has died has %d lives left", p_de->getPlayerId(), p_tempChar->getLives());

        df::Sound *p_sound = df::ResourceManager::getInstance().getSound("death");
        p_sound->play();

        return 1;
    }
    return 0;
}

void Organizer::startMatch() {
    //Get inputmanager to get number of joysticks connected
    df::InputManager &i_m = df::InputManager::getInstance();
    df::LogManager &l_m = df::LogManager::getInstance();
    df::WorldManager &w_m = df::WorldManager::getInstance();
    l_m.writeLog("Organizer::startMatch(): Match starting");
    // Start up the match, at stage, with character 1 and character 2

    //Load the stage;
    startStage();

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    //Delete the Icons for each stage
    world_manager.markForDelete(this->ut_icon);
    world_manager.markForDelete(this->vortex_icon);
    world_manager.markForDelete(this->vacation_icon);

    df::Position *start_pos_list = p_stage->getStartingPositions();

    int controllerNum = i_m.getJoystickCount();
    //Characters are located at index in array that matches their number. (0-4) 
    for (int i = 0; i < controllerNum; i++){
        l_m.writeLog("Organizer::startMatch(): Creating joystick player");
        //For each character, set the appropriate character class and controller
        Character *p_tempChar = NULL;
        LivesDisplay *tmpLD = new LivesDisplay();
        //Set to correct character (sets to NULL if character is None)
        p_tempChar = getCharacter(charArray[i]);

        if (p_tempChar != NULL){
            p_tempChar->setLives(numberOfLives);

            p_tempChar->registerInterest(df::JOYSTICK_EVENT);

            p_tempChar->setJoystickId(i); //Actual joystick ids are 0-4 

            //Set starting positions and colors
            switch (i){
                case 0:
                    p_tempChar->setObjectColor(df::RED);
                    p_tempChar->setPos(start_pos_list[0]);

                    tmpLD->setValue(p_tempChar->getLives());
                    tmpLD->setPos(df::Position(10, 21));
                    tmpLD->setColor(df::RED);
                    break;
                case 1:
                    p_tempChar->setObjectColor(df::BLUE);
                    p_tempChar->setPos(start_pos_list[1]);

                    tmpLD->setValue(p_tempChar->getLives());
                    tmpLD->setPos(df::Position(25, 21));
                    tmpLD->setColor(df::BLUE);
                    break;
                case 2:
                    p_tempChar->setObjectColor(df::YELLOW);
                    p_tempChar->setPos(start_pos_list[2]);

                    tmpLD->setValue(p_tempChar->getLives());
                    tmpLD->setPos(df::Position(40, 21));
                    tmpLD->setColor(df::YELLOW);
                    break;
                case 3:
                    p_tempChar->setObjectColor(df::MAGENTA);
                    p_tempChar->setPos(start_pos_list[3]);

                    tmpLD->setValue(p_tempChar->getLives());
                    tmpLD->setPos(df::Position(55, 21));
                    tmpLD->setColor(df::MAGENTA);
                    break;
            }
            this->char_obj_array[i] = p_tempChar;
            livesDisplayArray[i] = tmpLD;
        }
        else char_obj_array[i] = NULL;
    }

    // Start a keyboard player (Keyboard player only possible in 1v1 games.
    if (controllerNum < 2) {
        l_m.writeLog("Organizer::startMatch(): Creating keyboard player");
        //Keyboard player's character is stored in 4th element of array.
        Character *p_tempChar = NULL;

        p_tempChar = getCharacter(charArray[4]);

        if (p_tempChar != NULL){
            p_tempChar->setLives(numberOfLives);

            //Not a joystick so ID is 4
            p_tempChar->setJoystickId(4);

            p_tempChar->registerInterest(df::KEYBOARD_EVENT);

            p_tempChar->setObjectColor(df::MAGENTA);
            p_tempChar->setPos(start_pos_list[3]);
            this->char_obj_array[4] = p_tempChar;
            LivesDisplay *tmpLD = new LivesDisplay();
            tmpLD->setValue(p_tempChar->getLives());
            if (player_count == 1)
                tmpLD->setPos(df::Position(10, 21));
            else
                tmpLD->setPos(df::Position(25, 21));
            tmpLD->setColor(df::MAGENTA);
            livesDisplayArray[4] = tmpLD;
        }
        else char_obj_array[4] = NULL;
    }

    //set player names
    for (int i = 0; i < 5; i++){
        if (char_obj_array[i] != NULL){
            if (i < 4){
                std::ostringstream numString;
                numString << i + 1;
                std::string nameString = "Player " + numString.str();
                PlayerName *p_tempName = new PlayerName(nameString, char_obj_array[i]);
                char_obj_array[i]->setName(p_tempName);
            }
            else{
                if (player_count == 1)
                    char_obj_array[i]->setName(new PlayerName("Player 1", char_obj_array[i]));
                else
                    char_obj_array[i]->setName(new PlayerName("Player 2", char_obj_array[i]));
            }
        }
    }
    //Get rid of lives viewObjet
    this->state = GAME_SCREEN;
}

void Organizer::startStage() {
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    this->setSpriteIndex(2);
    this->setSpriteSlowdown(0);
    this->setAltitude(0);
    this->setPos(world_manager.getView().getPos());

    world_manager.setBoundary(df::Box(df::Position(), p_stage->getStageBounds().getHorizontal(), p_stage->getStageBounds().getVertical()));
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
        tmp_sel->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 4 + (i * 10), world_manager.getBoundary().getVertical() / 2));

        switch (i){
            case 0:
                tmp_sel->setObjectColor(df::RED);
                break;
            case 1:
                tmp_sel->setObjectColor(df::BLUE);
                break;
            case 2:
                tmp_sel->setObjectColor(df::YELLOW);
                break;
            case 3:
                tmp_sel->setObjectColor(df::MAGENTA);
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
    this->bull_icon = new Icon(BULL, "Bull");
    this->robot_icon = new Icon(ROBOT, "Robot");
    this->sgirl_icon = new Icon(SGIRL, "ScytheGirl");
    this->octopus_icon = new Icon(OCTOPUS, "Octopus");

    this->bull_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2,
        world_manager.getBoundary().getVertical() / 4));
    this->robot_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() * 3 / 4,
        world_manager.getBoundary().getVertical() / 4));
    this->sgirl_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 4,
        world_manager.getBoundary().getVertical() / 4));
    this->octopus_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2,
        world_manager.getBoundary().getVertical() * 2 / 4));


    df::WorldManager &w_m = df::WorldManager::getInstance();
    w_m.markForDelete(LivesCounter);
    this->state = CHARACTER_SCREEN;
}

void Organizer::selectStage(){
    df::InputManager &input_manager = df::InputManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();

    int controllersNum = input_manager.getJoystickCount();
    // Start a keyboard player; id is 5
    if (controllersNum < 1) {
        Selector *tmp_sel = new Selector;
        tmp_sel->setPlayerId(4);
        tmp_sel->setJoystickId(4);
        tmp_sel->unregisterInterest(df::JOYSTICK_EVENT);
        tmp_sel->registerInterest(df::KEYBOARD_EVENT);
        tmp_sel->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 2));
        tmp_sel->setObjectColor(df::MAGENTA);
        this->player_count++;
    } else {
        Selector *tmp_sel = new Selector;
        tmp_sel->setPlayerId(0);
        tmp_sel->setJoystickId(input_manager.getJoysticks()[0]);
        tmp_sel->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 2));
        tmp_sel->setObjectColor(df::RED);
        this->player_count++;
    }
    world_manager.markForDelete(this->bull_icon);
    world_manager.markForDelete(this->robot_icon);
    world_manager.markForDelete(this->sgirl_icon);
    world_manager.markForDelete(this->octopus_icon);

    //Create an icon for each of the stages
    this->ut_icon = new StageIcon(ULTIMATE_TERMINAL, "Terminal");
    this->vortex_icon = new StageIcon(VORTEX, "Vortex");
    this->vacation_icon = new StageIcon(VACATION, "Vacation");

    this->ut_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 2, world_manager.getBoundary().getVertical() / 4));
    this->vortex_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() * 3 / 4, world_manager.getBoundary().getVertical() / 4));
    this->vacation_icon->setPos(df::Position(world_manager.getBoundary().getHorizontal() / 4, world_manager.getBoundary().getVertical() / 4));

    this->state = STAGE_SCREEN;
}

Character *Organizer::getCharacter(Characters character){
    switch (character){
        case NONE:
            return NULL;
            break;
        case BULL:
            return new BullChar();
            break;
        case ROBOT:
            return new RobotChar();
            break;
        case SGIRL:
            return new ScytheGirlChar();
            break;
        case OCTOPUS:
            return new OctopusChar();
        default:
            break;
    }
}

void Organizer::draw() {
    df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
    if (state == GAME_SCREEN) {
        df::WorldManager &world_manager = df::WorldManager::getInstance();

        df::LogManager &l_m = df::LogManager::getInstance();
        int min_vert = 32766;
        int max_vert = -32766;
        int min_horiz = 32766;
        int max_horiz = -32766;
        for (int i = 0; i < 5; i++) {
            if (this->char_obj_array[i] != NULL) {
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
        }

        min_vert = std::max(0, min_vert - 16);
        max_vert = std::min(world_manager.getBoundary().getVertical(), max_vert + 16);
        min_horiz = std::max(0, min_horiz - 48);
        max_horiz = std::min(world_manager.getBoundary().getHorizontal(), max_horiz + 48);
        int temp_height = (max_horiz - min_horiz) / 4;
        world_manager.setView(df::Box(
            df::Position(min_horiz, (max_vert + min_vert - temp_height) / 2),
            max_horiz - min_horiz,
            temp_height)
            );
        this->setPos(world_manager.getView().getPos());
    }
    if (state == SPLASH_SCREEN) {
        Object::draw();
        graphics_manager.drawString(df::Position(5, 24), "Y [Key I] Lives +", df::LEFT_JUSTIFIED, df::WHITE);
        graphics_manager.drawString(df::Position(5, 25), "A [Key K] Lives -", df::LEFT_JUSTIFIED, df::WHITE);
    }

    if (this->state != SPLASH_SCREEN) {
        std::ostringstream i;
        i << characterCount;
        std::string CharacterNumberStr = "Characters Selected " + i.str();
    
        if (!charactersSelected){
            graphics_manager.drawString(df::Position(5, 25), "A [Key A] to Select", df::LEFT_JUSTIFIED, df::WHITE);
            graphics_manager.drawString(df::Position(5, 26), "B [Key X] to Cancel", df::LEFT_JUSTIFIED, df::WHITE);
            graphics_manager.drawString(df::Position(5, 27), CharacterNumberStr, df::LEFT_JUSTIFIED, df::WHITE);

        }
        else{
            graphics_manager.drawString(df::Position(5, 25), "Press Start [Key P] to Play", df::LEFT_JUSTIFIED, df::WHITE);
            graphics_manager.drawString(df::Position(5, 26), "B [Key X] to Cancel", df::LEFT_JUSTIFIED, df::WHITE);
            graphics_manager.drawString(df::Position(5, 27), CharacterNumberStr, df::LEFT_JUSTIFIED, df::WHITE);
        }
    }
}

bool Organizer::getMatchStarted() const{
    return this->state == GAME_SCREEN;
}

ScreenState Organizer::getState() const{
    return this->state;
}

int Organizer::getPlayerNum() const{
    return player_count;
}

LivesDisplay** Organizer::getLivesDisplay(){
    return livesDisplayArray;
}
