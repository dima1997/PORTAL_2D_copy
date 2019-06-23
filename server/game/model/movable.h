//
// Created by franciscosicardi on 23/06/19.
//

#ifndef PORTAL_MOVABLE_H
#define PORTAL_MOVABLE_H


#include <Box2D/Common/b2Settings.h>

class Movable {
private:
    float32 xPos;
    float32 yPos;
    virtual bool _changedPosition() = 0;
    virtual void _moveTo(float32 x, float32 y) = 0;
public:
    Movable(float32 xPos, float32 yPos);
    Movable(const Movable &other);
    virtual ~Movable();
    void moveTo(float32 x, float32 y);
    bool changedPosition();
};


#endif //PORTAL_MOVABLE_H
