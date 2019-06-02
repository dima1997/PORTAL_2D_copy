//
// Created by franciscosicardi on 19/05/19.
//

#ifndef PORTAL_WORLD_H
#define PORTAL_WORLD_H


#include <list>
#include <vector>
#include <Box2D/Dynamics/b2World.h>
#include "body/chell.h"
#include "map.h"
#include <protocol/event/object_moves_event.h>

class World {
private:
    b2Vec2 gravity;
    b2World *world;
    std::list<Chell *> chells;
    std::list<Body *> staticBodies;
    int numberOfPlayers;
    void loadMap(Map &map);
public:
    explicit World(Map &map);
//    World(World &&other) noexcept;
//    World &operator=(World &&other) noexcept;
    ~World();
    void step(std::list<std::shared_ptr<ObjectMovesEvent>> &moved);

    void moveChellLeft(uint32_t i);

    void moveChellRight(uint32_t i);

    void makeChellJump(uint32_t i);
};


#endif //PORTAL_WORLD_H
