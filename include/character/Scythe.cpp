/**
 * Scythe
 */

// Managers
#include "ResourceManager.h"

// Punchbowl headers
#include "Scythe.h"

Scythe::Scythe(ScytheGirlChar *init_scythe_girl) {

    this->scythe_girl = init_scythe_girl;
    this->setSolidness(df::SPECTRAL);
    this->setAltitude(1);
    this->setTransparency('#');
    this->setObjectColor(df::CYAN);

    this->relative_pos = df::Position();

    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    this->scythe_0_ccw = resource_manager.getSprite("scythe-0-ccw");
    this->scythe_0_cw = resource_manager.getSprite("scythe-0-cw");
    this->scythe_90_ccw = resource_manager.getSprite("scythe-90-ccw");
    this->scythe_90_cw = resource_manager.getSprite("scythe-90-cw");
    this->scythe_180_ccw = resource_manager.getSprite("scythe-180-ccw");
    this->scythe_180_cw = resource_manager.getSprite("scythe-180-cw");
    this->scythe_270_ccw = resource_manager.getSprite("scythe-270-ccw");
    this->scythe_270_cw = resource_manager.getSprite("scythe-270-cw");

    this->setSpriteSlowdown(0);
    //this->setSprite(this->scythe_0_ccw);
    this->updatePosition();
}


int Scythe::eventHandler(const df::Event *p_e) {
    return 0;
}

void Scythe::setRelativePos(df::Position new_pos) {
    this->relative_pos = new_pos;
}

void Scythe::updatePosition() {
    this->setPos(df::Position(
        scythe_girl->getPos().getX() + this->relative_pos.getX(),
        scythe_girl->getPos().getY() + this->relative_pos.getY()
        ));
}

void Scythe::draw() {
    this->updatePosition();
    df::Object::draw();
}

void Scythe::switchOrientation(ScytheOrientation orientation) {
    this->updatePosition();
    switch (orientation) {
        case SCYTHE_0_CW:
            this->setSprite(this->scythe_0_cw);
            break;
        case SCYTHE_0_CCW:
            this->setSprite(this->scythe_0_ccw);
            break;
        case SCYTHE_90_CW:
            this->setSprite(this->scythe_90_cw);
            break;
        case SCYTHE_90_CCW:
            this->setSprite(this->scythe_90_ccw);
            break;
        case SCYTHE_180_CW:
            this->setSprite(this->scythe_180_cw);
            break;
        case SCYTHE_180_CCW:
            this->setSprite(this->scythe_180_ccw);
            break;
        case SCYTHE_270_CW:
            this->setSprite(this->scythe_270_cw);
            break;
        case SCYTHE_270_CCW:
            this->setSprite(this->scythe_270_ccw);
            break;
        default:
            this->setSprite(this->scythe_0_cw);
            break;
    }
}
