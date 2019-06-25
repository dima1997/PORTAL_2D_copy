//
// Created by franciscosicardi on 19/05/19.
//

#include <cstdio>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "world.h"

#include <portal_exception.h>
#include <protocol/event/player_wins_event.h>
#include <protocol/event/player_dies_event.h>
#include <protocol/event/object_switch_event.h>
#include <protocol/event/grab_rock_event.h>
#include <protocol/event/throw_rock_event.h>
#include <protocol/event/player_loses_event.h>
#include <protocol/event/portal_moves_event.h>
#include <protocol/event/player_reach_cake_event.h>
#include "yaml-cpp/yaml.h"
#include "contact_listener/contact_listener.h"
#include "../config/global_configuration.h"

World::World(Map &map): world(new b2World(b2Vec2(CONFIG.gravityX, CONFIG.gravityY))), contactListener(), contactFilter(),
                        numberOfPlayers(map.getPlayersNumber()), finished(false), chells(map.loadChells(*world)),
                        blocks(map.loadBlocks(*world)), doors(map.loadDoors(*world)),
                        buttons(map.loadButtons(*world, doors)), rocks(map.loadRocks(*world)),
                        barriers(map.loadBarriers(*world)), emitters(map.loadEmitters(*world)), receivers(map.loadReceivers(*world, doors)),
                        balls(map.loadBalls(*world, emitters)), cakes(map.loadCakes(*world)) {
    world->SetContactListener(&contactListener);
    world->SetContactFilter(&contactFilter);
    for (auto &chell : chells) {
        movables.insert(std::make_pair(chell.getId(), std::reference_wrapper<MovableBody>(chell)));
        PinTool &pinTool = chell.getPinTool();
        movables.insert(std::make_pair(pinTool.getId(), std::reference_wrapper<MovableBody>(pinTool)));
        switchables.insert(std::make_pair(pinTool.getId(), std::reference_wrapper<Switchable>(pinTool)));
        Portal &blue = chell.getPortal(BLUE);
        switchables.insert(std::make_pair(blue.getId(), std::reference_wrapper<Switchable>(blue)));
        Portal &orange = chell.getPortal(ORANGE);
        switchables.insert(std::make_pair(orange.getId(), std::reference_wrapper<Switchable>(orange)));
    }
    for (auto &elem : doors) {
        switchables.insert(std::make_pair(elem.getId(), std::reference_wrapper<Switchable>(elem)));
    }
    for (auto &elem : buttons) {
        switchables.insert(std::make_pair(elem.getId(), std::reference_wrapper<Switchable>(elem)));
    }
    for (auto &elem : rocks) {
        movables.insert(std::make_pair(elem.getId(), std::reference_wrapper<MovableBody>(elem)));
    }
    for (auto &elem : receivers) {
        switchables.insert(std::make_pair(elem.getId(), std::reference_wrapper<Switchable>(elem)));
    }
    for (auto &elem : balls) {
        movables.insert(std::make_pair(elem.getId(), std::reference_wrapper<MovableBody>(elem)));
    }
}

void World::step(std::list<std::shared_ptr<Event>> &events) {

    float32 timeStep = CONFIG.timeStepSeconds;

    int32 velocityIterations = CONFIG.velocityIterations;
    int32 positionIterations = CONFIG.positionIterations;

    bool won = false;

    world->Step(timeStep, velocityIterations, positionIterations);

    processMoveEvents(events);
    processSwitchEvents(events);
    processChellEvents(won, events);

}

World::~World() {
    delete world;
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

bool World::gameEnded(bool won, std::list<std::shared_ptr<Event>> &events) {
    if (--numberOfPlayers == 0) {
        if (won) {
            events.push_back(std::shared_ptr<Event>(new PlayerWinsEvent()));
        } else {
            events.push_back(std::shared_ptr<Event>(new PlayerLosesEvent()));
        }
        finished = true;
        return true;
    }
    return false;
}

void World::processMoveEvents(std::list<std::shared_ptr<Event>> &events) {
    for (auto &movable : movables) {
        uint8_t id = movable.first;
        MovableBody &body = movable.second.get();
        if (body.changedPosition()) {
            events.push_back(
                    std::shared_ptr<Event>(new ObjectMovesEvent(id, body.getXPos(), body.getYPos())));
        }
    }
}

void World::processSwitchEvents(std::list<std::shared_ptr<Event>> &events) {
    for (auto &switchable : switchables) {
        uint8_t id = switchable.first;
        Switchable &elem = switchable.second.get();
        if (elem.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(id)));
        }
    }
}

void World::processChellEvents(bool won, std::list<std::shared_ptr<Event>> &events) {
    for (Chell &chell : chells) {
        switch (chell.getState()) {
            case DIED_C:
                chell.finish();
                events.push_back(std::shared_ptr<Event>(new PlayerDiesEvent(chell.getId())));
                if (gameEnded(won, events)) {
                    return;
                }
                break;
            case REACHED_CAKE_C:
                chell.finish();
                won = true;
                events.push_back(std::shared_ptr<Event>(new PlayerReachCakeEvent(chell.getId())));
                if (gameEnded(won, events)) {
                    return;
                }
                break;
            case FINISHED_C:
            case PLAYING_C:
                if (chell.grabbedRock()) {
                    events.push_back(std::shared_ptr<Event>(new GrabRockEvent(chell.getId(), chell.getRock().getId())));
                }
                if (chell.threwRock()) {
                    events.push_back(std::shared_ptr<Event>(new ThrowRockEvent(chell.getRock().getId())));
                }
                Portal &orange = chell.getPortal(ORANGE);
                if (orange.changedPosition()) {
                    events.push_back(std::shared_ptr<Event>(
                            new PortalMovesEvent(orange.getId(), orange.getXPos(), orange.getYPos(), chell.getId(), orange.getNormalX(), orange.getNormalY())));
                }
                Portal &blue = chell.getPortal(BLUE);
                if (blue.changedPosition()) {
                    events.push_back(std::shared_ptr<Event>(
                            new PortalMovesEvent(blue.getId(), blue.getXPos(), blue.getYPos(), chell.getId(), blue.getNormalX(), blue.getNormalY())));
                }
                break;
        }
    }
}
