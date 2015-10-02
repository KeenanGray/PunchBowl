#ifndef __PLATFORM_H__
#define __PLATFORM_H__

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

class Platform : public df::Object{
private:
public:
    Platform();
    ~Platform();

    int eventHandler(const df::Event *p_e);
};


#endif