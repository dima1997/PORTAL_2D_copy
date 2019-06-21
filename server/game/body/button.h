//
// Created by franciscosicardi on 09/06/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H


#include <list>
#include "body.h"
#include "door.h"

class Button: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    std::list<std::reference_wrapper<Door>> doors;
    int contactCount;
    void updateDoors(bool status);
    bool updated;
public:
    Button(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::list<std::reference_wrapper<Door>> &doors);
    Button(Button &&other) noexcept;
    ~Button() override;
    body_type_t getBodyType() override;
    void increaseContact();
    void decreaseContact();
    bool wasUpdated();
};


#endif //PORTAL_BUTTON_H
