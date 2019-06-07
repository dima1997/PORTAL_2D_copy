//
// Created by franciscosicardi on 19/05/19.
//

#include <cstdio>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "world.h"
#include "body/block.h"

#include <configs_yaml/config_paths.h>
#include <portal_exception.h>
#include <protocol/event/player_wins_event.h>
#include <protocol/event/player_dies_event.h>
#include "yaml-cpp/yaml.h"
#include "contact_listeners/contact_listener.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 2

World::World(Map &map): gravity(0.0f, -9.8f), world(new b2World(gravity)),
                              chells(), staticBodies(), cake(), numberOfPlayers(), finished(false) {
    loadMap(map);
    std::unique_ptr<ContactListener> contactListener(new ContactListener());
    world->SetContactListener(contactListener.get());
    listeners.push_back(std::move(contactListener));
}

void World::step(std::list<std::shared_ptr<Event>> &events) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    for (Chell *chell : chells) {
        chell->update();
    }

    world->Step(timeStep, velocityIterations, positionIterations);

    if (cake->wasReached()) {
        events.push_back(std::shared_ptr<Event>(new PlayerWinsEvent()));
        finished = true;
        return;
    }
    for (Chell *chell : chells) {
        if ( (this->idPlayersDead.count(chell->getId()) == 0) && (!chell->isAlive()) ) {
            if (--numberOfPlayers == 0) {
                finished = true;
            }
            this->idPlayersDead.insert(chell->getId());
            events.push_back(std::shared_ptr<Event>(new PlayerDiesEvent(chell->getId())));
            break;
        }
        if (chell->changedPosition()) {
            events.push_back(
                    std::shared_ptr<Event>(new ObjectMovesEvent(chell->getId(), chell->getXPos(), chell->getYPos())));
        }
        Portal *orange = chell->getOrangePortal();
        if (orange->changedPosition()) {
            events.push_back(std::shared_ptr<Event>(
                    new ObjectMovesEvent(orange->getId(), orange->getXPos(), orange->getYPos())));
        }
        Portal *blue = chell->getBluePortal();
        if (blue->changedPosition()) {
            events.push_back(
                    std::shared_ptr<Event>(new ObjectMovesEvent(blue->getId(), blue->getXPos(), blue->getYPos())));
        }
    }

}

World::~World() {
    for (auto *chell : chells) {
        delete chell;
    }
    for(auto *body : staticBodies) {
        delete body;
    }
    delete cake;
    delete world;
}

void World::loadMap(Map &map) {
    map.loadBlocks(*world, staticBodies);
    cake = map.loadCake(*world);
    map.loadChells(*world, chells);
    numberOfPlayers = map.getPlayersNumber();
}

Chell *World::getChell(uint32_t i) {
    for (auto *chell : chells) {
        if (chell->getId() == i) {
            return chell;
        }
    }
    std::stringstream s;
    s << "Inexistent Chell with id " << i;
    throw PortalException(s.str());
}

bool World::hasFinished() {
    return finished;
}
