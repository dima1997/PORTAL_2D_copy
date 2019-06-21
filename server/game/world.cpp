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
#include <protocol/event/object_switch_event.h>
#include <protocol/event/grab_rock_event.h>
#include <protocol/event/throw_rock_event.h>
#include <protocol/event/player_loses_event.h>
#include <protocol/event/portal_moves_event.h>
#include "yaml-cpp/yaml.h"
#include "contact_listener/contact_listener.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 2

World::World(Map &map): gravity(0.0f, -9.8f), world(new b2World(gravity)), contactListener(), contactFilter(),
                        numberOfPlayers(), finished(false), chells(std::move(map.loadChells(*world))),
                        blocks(std::move(map.loadBlocks(*world))), cake(std::move(map.loadCake(*world))) {
    loadMap(map);
    world->SetContactListener(&contactListener);
    world->SetContactFilter(&contactFilter);
}

void World::step(std::list<std::shared_ptr<Event>> &events) {

    float32 timeStep = TIME_STEP;

    int32 velocityIterations = VELOCITY_ITERATIONS;
    int32 positionIterations = POSITION_ITERATIONS;

    for (Chell &chell : chells) {
        chell.update();
    }

    world->Step(timeStep, velocityIterations, positionIterations);

    if (cake.wasReached()) {
        events.push_back(std::shared_ptr<Event>(new PlayerWinsEvent()));
        finished = true;
        return;
    }
    for (Button *button : buttons) {
        if (button->wasUpdated()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(button->getId())));
        }
    }
    for (Door *door : doors) {
        if (door->update()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(door->getId())));
        }
    }
    for (EnergyBall *ball : balls) {
        ball->changedPosition();
        ball->move();
        events.push_back(std::shared_ptr<Event>(new ObjectMovesEvent(ball->getId(), ball->getXPos(), ball->getYPos())));
    }
    for (Chell &chell : chells) {
        if ( chell.justDied() ) {
            events.push_back(std::shared_ptr<Event>(new PlayerDiesEvent(chell.getId())));
            if (--numberOfPlayers == 0) {
                events.push_back(std::shared_ptr<Event>(new PlayerLosesEvent()));
                finished = true;
                return;
            }
            break;
        }
        if (chell.changedPosition()) {
            events.push_back(
                    std::shared_ptr<Event>(new ObjectMovesEvent(chell.getId(), chell.getXPos(), chell.getYPos())));
        }
        if (chell.grabbedRock()) {
            events.push_back(std::shared_ptr<Event>(new GrabRockEvent(chell.getId(), chell.getRock()->getId())));
        }
        if (chell.threwRock()) {
            events.push_back(std::shared_ptr<Event>(new ThrowRockEvent(chell.getRock()->getId())));
        }
        Portal *orange = chell.getPortal(ORANGE);
        if (orange->changedPosition()) {
            events.push_back(std::shared_ptr<Event>(
                    //new ObjectMovesEvent(orange->getId(), orange->getXPos(), orange->getYPos())));
                    new PortalMovesEvent(orange->getId(), orange->getXPos(), orange->getYPos(), chell.getId())));
        }
        Portal *blue = chell.getPortal(BLUE);
        if (blue->changedPosition()) {
            events.push_back(
                    //std::shared_ptr<Event>(new ObjectMovesEvent(blue->getId(), blue->getXPos(), blue->getYPos())));
                    std::shared_ptr<Event>(
                        new PortalMovesEvent(blue->getId(), blue->getXPos(), blue->getYPos(), chell.getId())));
        }
    }
    for (Rock *rock : rocks) {
        if (rock->changedPosition()) {
            events.push_back(std::shared_ptr<Event>(new ObjectMovesEvent(rock->getId(), rock->getXPos(), rock->getYPos())));
        }
    }

}

World::~World() {
    // TODO: all to the stack
//    for (auto *chell : chells) {
//        delete chell;
//    }
//    for(auto *block : blocks) {
//        delete block;
//    }
    for(auto *button : buttons) {
        delete button;
    }
    for(auto *door : doors) {
        delete door;
    }
    for(auto *rock : rocks) {
        delete rock;
    }
    for(auto *barrier: barriers) {
        delete barrier;
    }
    for(auto *emitter: emitters) {
        delete emitter;
    }
//    delete cake;
    delete world;
}

void World::loadMap(Map &map) {
//    map.loadBlocks(*world, blocks);
//    cake = map.loadCake(world);
//    map.loadChells(world, chells);
    map.loadDoors(*world, doors);
    map.loadButtons(*world, buttons, doors);
    map.loadRocks(*world, rocks);
    map.loadBarriers(*world, barriers);
    map.loadEmitters(*world, emitters);
    map.loadBalls(*world, balls, emitters);
    numberOfPlayers = map.getPlayersNumber();
}

Chell &World::getChell(uint32_t i) {
    for (auto &chell : chells) {
        if (chell.getId() == i) {
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
