//
// Created by franciscosicardi on 19/05/19.
//

#ifndef PORTAL_WORLD_H
#define PORTAL_WORLD_H


#include <list>
#include <vector>
#include <Box2D/Dynamics/b2World.h>
#include "body/chell.h"
#include "protocol/object_moves_event.h"

class World {
private:
    b2Vec2 gravity;
    b2World *world;
    std::list<Chell *> chells;
    std::list<Body *> staticBodies;
    void loadMap(uint8_t mapId);
public:
    explicit World(uint8_t map_id);
    World(World &&other) noexcept;
    World &operator=(World &&other) noexcept;
    ~World();
    void step(std::list<ObjectMovesEvent> &moved);
};


#endif //PORTAL_WORLD_H
