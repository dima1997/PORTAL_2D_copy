//
// Created by franciscosicardi on 25/05/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "block.h"

Block::Block(b2World &world, float32 xPos, float32 yPos, body_type_t type, uint32_t id, orientation_t orientation):
           Body(world, xPos, yPos, id), type(type), orientation(orientation) {
    createBody(xPos, yPos);
}

Block::~Block() = default;

void Block::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);
    switch (orientation) {
        case SQUARE:
            createSquare();
            break;
        case BOTTOM_LEFT:
            createBottomLeft();
            break;
        case BOTTOM_RIGHT:
            createBottomRight();
            break;
        case TOP_LEFT:
            createTopLeft();
            break;
        case TOP_RIGHT:
            createTopRight();
            break;
    }
}

body_type_t Block::getBodyType() {
    return type;
}

void Block::createSquare() {
    b2PolygonShape box;
    box.SetAsBox(0.5f, 0.5f);
    body->CreateFixture(&box, 0.0f);
}

void Block::createTopLeft() {
    b2Vec2 vertices[3];
    vertices[0].Set(-0.5f, 0.5f);
    vertices[1].Set(0.5f, 0.5f);
    vertices[2].Set(-0.5f, -0.5f);
    b2PolygonShape triangle;
    triangle.Set(vertices, 3);
    body->CreateFixture(&triangle, 0.0f);
}

void Block::createBottomLeft() {
    b2Vec2 vertices[3];
    vertices[0].Set(-0.5f, 0.5f);
    vertices[1].Set(0.5f, -0.5f);
    vertices[2].Set(-0.5f, -0.5f);
    b2PolygonShape triangle;
    triangle.Set(vertices, 3);
    body->CreateFixture(&triangle, 0.0f);
}

void Block::createBottomRight() {
    b2Vec2 vertices[3];
    vertices[0].Set(0.5f, 0.5f);
    vertices[1].Set(0.5f, -0.5f);
    vertices[2].Set(-0.5f, -0.5f);
    b2PolygonShape triangle;
    triangle.Set(vertices, 3);
    body->CreateFixture(&triangle, 0.0f);
}

void Block::createTopRight() {
    b2Vec2 vertices[3];
    vertices[0].Set(-0.5f, 0.5f);
    vertices[1].Set(0.5f, -0.5f);
    vertices[2].Set(0.5f, 0.5f);
    b2PolygonShape triangle;
    triangle.Set(vertices, 3);
    body->CreateFixture(&triangle, 0.0f);
}

Block::Block(const Block &other): Body(other), type(other.type), orientation(other.orientation) {}
