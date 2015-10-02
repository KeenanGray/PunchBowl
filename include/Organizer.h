#ifndef __ORGANIZER_H__
#define __ORGANIZER_H__

//Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Object.h"
#include "EventKeyboard.h"
#include "EventStep.h"
#include "EventJoystick.h"

//Game includes

class Organizer : public df::Object{
private:
        Organizer(); //Private constructor for singleton
        Organizer(Organizer const&);  //prevents copying
        void operator = (Organizer const&); //prevents 

public:
    static Organizer &getInstance();
    int eventHandler(const df::Event *p_e);
};


#endif