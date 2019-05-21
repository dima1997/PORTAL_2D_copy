//
// Created by franciscosicardi on 19/05/19.
//

#ifndef PORTAL_BODY_INFO_H
#define PORTAL_BODY_INFO_H


#include <Box2D/Common/b2Settings.h>
#include <utility>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

class BodyInfo {
private:
    unsigned int id;
    b2Vec2 position;
    bool updated;
public:
    BodyInfo(unsigned int id, b2Vec2 position);
    virtual ~BodyInfo();
    void update(b2Vec2 pos);
    bool isUpdated();
    b2Vec2 getPosition();
};


#endif //PORTAL_BODY_INFO_H
