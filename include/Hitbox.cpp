/**
 * Hitbox class
 */

// Dragonfly Engine headers
// Managers
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Punchbowl headers
#include "Hitbox.h"

Hitbox::Hitbox(
            Character *init_origin, 
            df::Position init_relative_pos, 
            int init_stun,
            int init_damage,
            float init_knockback,
            df::Position init_direction,
            int width,
            int height
            ) {


    // Set type attribute
    setType(hitbox_type);
    this->setSolidness(df::SOFT);
    this->setAltitude(3);

    // Register interest for events
    this->registerInterest(df::STEP_EVENT);

    this->p_origin = init_origin;
    this->relative_pos = init_relative_pos;
    this->width = width;
    this->height = height;

    this->stun = init_stun;
    this->damage = init_damage;
    this->knockback = init_knockback;
    this->direction = init_direction;

    this->hit_count = 0;

    this->updateWorldPos();
}

void Hitbox::updateWorldPos() {
    this->setPos(df::Position(
        this->relative_pos.getX() + this->p_origin->getPos().getX(), 
        this->relative_pos.getY() + this->p_origin->getPos().getY()
        ));
}

int Hitbox::eventHandler(const df::Event *p_e) {
    if (p_e->getType().compare(df::STEP_EVENT) == 0) {
        return this->step();
    }
    return 0;
}

int Hitbox::step() {
    this->updateWorldPos();

    df::Box detection_box = df::Box(this->getPos(), this->width, this->height);

    df::ObjectList obj_hit = df::WorldManager::getInstance().objectsInBox(detection_box);

    df::ObjectListIterator li(&obj_hit);
    for (li.first(); !li.isDone(); li.next()) {
        df::Object *p_o = li.currentObject();
        Character *p_char;
        if (p_char = dynamic_cast<Character *> (p_o)) {
            if (p_o->getId() != this->p_origin->getId()) {
                bool not_hit_yet = true;
                for (int i = 0; i < this->hit_count; i++) {
                    if (this->already_hit[i] == p_o->getId()) {
                        not_hit_yet = false;
                    }
                }
                if (not_hit_yet) {
                    df::LogManager::getInstance().writeLog("Hitbox::step(): Hit object id %d for %d damage.", p_char->getId(), this->damage);
                    p_char->hit(this);
                    this->already_hit[this->hit_count] = p_o->getId();
                    this->hit_count++;
                }
            }
        }
    }

    return 0;
}

void Hitbox::setStun(int new_stun) {
    this->stun = new_stun;
}

int Hitbox::getStun() const {
    return this->stun;
}

void Hitbox::setDamage(int new_damage) {
    this->damage = new_damage;
}

int Hitbox::getDamage() const {
    return this->damage;
}

void Hitbox::setKnockback(float new_knockback) {
    this->knockback = new_knockback;
}

float Hitbox::getKnockback() const {
    return this->knockback;
}

void Hitbox::setDirection(df::Position new_direction) {
    this->direction = new_direction;
}

df::Position Hitbox::getDirection() const {
    return this->direction;
}

void Hitbox::draw() {/*
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            df::Position temp_pos = df::Position(this->getPos().getX()+i, this->getPos().getY()+j);
            df::GraphicsManager::getInstance().drawCh(temp_pos, '*', df::YELLOW);
        }
    }*/
}
