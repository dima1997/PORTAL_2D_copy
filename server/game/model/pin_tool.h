//
// Created by franciscosicardi on 22/06/19.
//

#ifndef PORTAL_PIN_TOOL_H
#define PORTAL_PIN_TOOL_H


#include <Box2D/Common/b2Timer.h>
#include "movable_body.h"
#include "switchable.h"

class PinTool: public MovableBody, public Switchable {
private:
    void customizeBody() override;
    bool _switchedState(bool updated) override;
    b2Timer timer;
    bool visible;
public:
    PinTool(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    PinTool(const PinTool &other);
    ~PinTool() override;
    body_type_t getBodyType() override;
    void show(float32 x, float32 y);
};


#endif //PORTAL_PIN_TOOL_H
