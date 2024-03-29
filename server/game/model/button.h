//
// Created by franciscosicardi on 09/06/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H


#include <list>
#include "body.h"
#include "door.h"

class Button: public Body, public Switchable {
private:
    void customizeBody() override;
    std::list<std::reference_wrapper<Door>> doors;
    int contactCount;
    void _switchState() override;
public:
    Button(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<std::reference_wrapper<Door>> &doors);
    Button(const Button &other);
    ~Button() override;
    body_type_t getBodyType() override;
    void increaseContact();
    void decreaseContact();
};


#endif //PORTAL_BUTTON_H
