//
// Created by franciscosicardi on 19/05/19.
//

#ifndef PORTAL_WORLD_H
#define PORTAL_WORLD_H


#include <list>
#include <Box2D/Dynamics/b2World.h>
#include "body.h"

class World {
private:
    b2Vec2 gravity;
    b2World *world;
    void loadMap(uint8_t mapId);
public:
    explicit World(uint8_t map_id);
    World(World &&other) noexcept;
    World &operator=(World &&other) noexcept;
    ~World();
    void step(std::list<Body *> &updated);
};


#endif //PORTAL_WORLD_H
