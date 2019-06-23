//
// Created by franciscosicardi on 19/05/19.
//

#ifndef PORTAL_WORLD_H
#define PORTAL_WORLD_H


#include <list>
#include <vector>
#include <Box2D/Dynamics/b2World.h>
#include "model/chell.h"
#include "map.h"
#include "model/block.h"
#include "model/cake.h"
#include "model/door.h"
#include "model/button.h"
#include "model/rock.h"
#include "model/energy_ball.h"
#include "contact_listener/contact_listener.h"
#include "contact_filter/contact_filter.h"
#include <protocol/event/object_moves_event.h>

#include <set>

class World {
private:
    b2Vec2 gravity;
    b2World *world;
    std::list<Chell> chells;
    std::list<Block> blocks;
    std::list<Door> doors;
    std::list<Button> buttons;
    std::list<Rock> rocks;
    std::list<Barrier> barriers;
    std::list<EnergyEmitter> emitters;
    std::list<EnergyReceiver> receivers;
    std::list<EnergyBall> balls;
    ContactListener contactListener;
    ContactFilter contactFilter;
    Cake cake;
    int numberOfPlayers;
    bool finished;
public:
    explicit World(Map &map);
    bool hasFinished();
    ~World();
    void step(std::list<std::shared_ptr<Event>> &events);
    Chell &getChell(uint32_t i);
};


#endif //PORTAL_WORLD_H
