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
#include "body/cake.h"
#include <protocol/event/object_moves_event.h>

class World {
private:
    b2Vec2 gravity;
    b2World *world;
    std::list<Chell *> chells;
    std::list<Body *> staticBodies;
    Cake *cake;
    std::vector<std::shared_ptr<b2ContactListener>> listeners;
    int numberOfPlayers;
    bool finished;
    void loadMap(Map &map);
public:
    explicit World(Map &map);
    bool hasFinished();
    ~World();
    void step(std::list<std::shared_ptr<Event>> &events);
    Chell *getChell(uint32_t i);
};


#endif //PORTAL_WORLD_H
