/**
 * Hitbox class header
 *
 * They are created during attacks and cause damage and knockback
 */

#ifndef __HITBOX_H__
#define __HITBOX_H__

// Dragonfly Engine headers
// Object
#include "Object.h"

//Game Includes
#include "character/Character.h"

class Character;

const std::string hitbox_type = "hitbox";

class Hitbox : public df::Object {
    private:
        // Hitbox must be constructed with initial values
        Hitbox();

        // The character this hitbox originated from
        Character *p_origin;
        // The location of the hitbox in the world
        df::Position world_pos;
        // The location of the hitbox relative to the character
        df::Position relative_pos;
        // Dimensions of the hitbox
        int width;
        int height;

        // Frames stunned for
        int stun;
        // Amount of damage dealt
        int damage;
        // Amount of knockback
        float knockback;
        // Direction to push the hit entities
        df::Position direction;

        // List of ids of characters already hit by this hitbox
        int already_hit[4];
        // Number of characters hit by this attack
        int hit_count;

        // Updates the world position of the hitbox
        void updateWorldPos();

        // Finds characters collided with and calls hit on them
        int step();

    public:
        Hitbox(
            Character *init_origin, 
            df::Position init_relative_pos, 
            int init_stun,
            int init_damage,
            float init_knockback,
            df::Position init_direction,
            int init_width = 1,
            int init_height = 1
            );
        
        int eventHandler(const df::Event *p_e);

        void setStun(int new_stun);
        int getStun() const;
        void setDamage(int new_damage);
        int getDamage() const;
        void setKnockback(float new_knockback);
        float getKnockback() const;
        void setDirection(df::Position new_direction);
        df::Position getDirection() const;

        virtual void draw();

};

#endif // __HITBOX_H__
