// dragonfly headers
#include "Event.h"
#include "EventKeyboard.h"
#include "EventView.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ResourceManager.h"
#include "ViewObject.h"
#include "WorldManager.h"
#include "utility.h"

#include <algorithm>

class TestObj : public df::Object {
private:

public:
    TestObj();
    int eventHandler(const df::Event *p_e);
};

TestObj::TestObj() {
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
    this->setSprite(resource_manager.getSprite("test"));

    this->setType("TestObject");

    this->registerInterest(df::KEYBOARD_EVENT);
    this->registerInterest(df::STEP_EVENT);
}

int TestObj::eventHandler(const df::Event *p_e) {
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard *keyboard_event = static_cast<const df::EventKeyboard *> (p_e);
        if (keyboard_event->getKey() == df::Input::Q) {
            df::GameManager &game_manager = df::GameManager::getInstance();
            game_manager.setGameOver();
        }
        else if (this->getXVelocity() > 0.2 && keyboard_event->getAction() == df::KEY_PRESSED) {
            if (keyboard_event->getKey() == df::Input::P) {
                df::EventView ev("test", 1, true);
                world_manager.onEvent(&ev);
            }
            else if (keyboard_event->getKey() == df::Input::O) {
                df::EventView ev("test", -1, true);
                world_manager.onEvent(&ev);
            }
            else if (keyboard_event->getKey() == df::Input::I) {
                df::EventView ev("test", 10, false);
                world_manager.onEvent(&ev);
            }
        }
        return 1;
    }
    else if (p_e->getType() == df::STEP_EVENT && this->getXVelocity() > 0.2) {
        int temp_width = std::min(120, std::max(2 * (116 - this->getPos().getX()), 60));
        world_manager.setView(df::Box(world_manager.getView().getPos(), temp_width, temp_width / 3));
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // Game manager will startup log manager automatically, but
    // I want to startup log_manager with logging level 0. 
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.startUp(0);
    log_manager.setFlush(true);

    df::GameManager &game_manager = df::GameManager::getInstance();
    game_manager.startUp();

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    // Load sprite
    resource_manager.loadSprite("Sprites/testsprite.txt", "test");

    log_manager.writeLog("Testing Boxes and views and boundaries");

    // Populate world
    df::ViewObject *t2 = new df::ViewObject();
    t2->setViewString("test");
    df::ViewObject *t3 = new df::ViewObject(false, df::CENTER_CENTER, df::GREEN);
    t3->setViewString("test");
    df::ViewObject *t4 = new df::ViewObject(true, df::BOTTOM_RIGHT, df::YELLOW);
    t4->setViewString("test");

    TestObj *t1 = new TestObj();
    t1->setPos(df::Position(4, 15));
    t1->setSpriteSlowdown(0);
    t1->setXVelocity(0.5);

    TestObj *t5 = new TestObj();
    t5->setPos(df::Position(30, 20));
    t5->setSpriteSlowdown(15);

    TestObj *t6 = new TestObj();
    t6->setPos(df::Position(117, 20));
    t6->setSpriteSlowdown(14);

    TestObj *t10 = new TestObj();
    t10->setPos(df::Position(118, 10));
    t10->setSpriteSlowdown(14);

    TestObj *t11 = new TestObj();
    t11->setPos(df::Position(119, 5));
    t11->setSpriteSlowdown(14);

    TestObj *t12 = new TestObj();
    t12->setPos(df::Position(120, 25));
    t12->setSpriteSlowdown(14);

    TestObj *t7 = new TestObj();
    t7->setPos(df::Position(90, 20));
    t7->setSpriteSlowdown(13);

    TestObj *t8 = new TestObj();
    t8->setPos(df::Position(78, 20));
    t8->setSpriteSlowdown(12);

    TestObj *t9 = new TestObj();
    t9->setPos(df::Position(77, 10));
    t9->setSpriteSlowdown(12);

    df::WorldManager &world_manager = df::WorldManager::getInstance();

    world_manager.setViewFollowing(t1);
    world_manager.setBoundary(df::Box(df::Position(), 120, 256));
    world_manager.setView(df::Box(world_manager.getView().getPos(), 96, 32));

    // Run game
    game_manager.run();

    game_manager.shutDown();

    return 0;
}