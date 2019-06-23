//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_BLOCK_H
#define PORTAL_BLOCK_H


#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include "body.h"

typedef enum orientation {SQUARE, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT} orientation_t;

class Block: public Body {
private:
    void customizeBody() override;
    body_type_t type;
    orientation_t orientation;
    void createSquare();
    void createTopLeft();
    void createBottomLeft();
    void createBottomRight();
    void createTopRight();
public:
    Block(b2World &world, float32 xPos, float32 yPos, body_type_t type, uint32_t id, orientation_t orientation);
    Block(const Block &other);
    ~Block() override;
    body_type_t getBodyType() override;
};


#endif //PORTAL_BLOCK_H
