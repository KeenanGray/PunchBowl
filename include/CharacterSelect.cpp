#include "CharacterSelect.h"

CharacterSelect::CharacterSelect(){
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    setType("Selector");

    registerInterest(df::JOYSTICK_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);

    df::Sprite *tmp_spr = resource_manager.getSprite("selector");
    setSprite(tmp_spr);

}

int CharacterSelect::eventHandler(const df::Event *p_e){

    return 0;
}

//get and set id
void CharacterSelect::setPlayer(int new_player){
    player = new_player;
}
int CharacterSelect::getPlayer() const{
    return player;
}

//get and set character
void CharacterSelect::setCharacter(Character *new_char){
    character = new_char;
}
Character CharacterSelect::getCharacter() const{
    return *character;
}