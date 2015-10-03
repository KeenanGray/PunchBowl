#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {
private:
    void start();
    df::Music *p_music;

public:
    GameStart();
    int eventHandler(const df::Event *p_e);
    void draw();
    void playMusic();
};

