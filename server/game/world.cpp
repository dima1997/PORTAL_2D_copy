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
                        balls(map.loadBalls(*world, emitters)), cake(map.loadCake(*world)) {
    world->SetContactListener(&contactListener);
    world->SetContactFilter(&contactFilter);
}

void World::step(std::list<std::shared_ptr<Event>> &events) {

    float32 timeStep = CONFIG.timeStepSeconds;

    int32 velocityIterations = CONFIG.velocityIterations;
    int32 positionIterations = CONFIG.positionIterations;

    bool won = false;

    world->Step(timeStep, velocityIterations, positionIterations);

    for (Button &button : buttons) {
        if (button.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(button.getId())));
        }
    }
    for (EnergyReceiver &receiver: receivers) {
        if (receiver.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(receiver.getId())));
        }
    }
    for (Door &door : doors) {
        if (door.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(door.getId())));
        }
    }
    for (EnergyBall &ball : balls) {
        ball.changedPosition();
        events.push_back(std::shared_ptr<Event>(new ObjectMovesEvent(ball.getId(), ball.getXPos(), ball.getYPos())));
    }
    for (Chell &chell : chells) {
        if (chell.getState() == FINISHED_C) {
            continue;
        }
        if (chell.getState() == DIED_C) {
            chell.finish();
            events.push_back(std::shared_ptr<Event>(new PlayerDiesEvent(chell.getId())));
            if (gameEnded(won, events)) {
                return;
            }
            break;
        }
        if (chell.getState() == REACHED_CAKE_C) {
            chell.finish();
            won = true;
            events.push_back(std::shared_ptr<Event>(new PlayerReachCakeEvent(chell.getId())));
            if (gameEnded(won, events)) {
                return;
            }
            break;
        }
        if (chell.changedPosition()) {
            events.push_back(
                    std::shared_ptr<Event>(new ObjectMovesEvent(chell.getId(), chell.getXPos(), chell.getYPos())));
        }
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
        } else if (orange.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(orange.getId())));
        }
        Portal &blue = chell.getPortal(BLUE);
        if (blue.changedPosition()) {
            events.push_back(std::shared_ptr<Event>(
                    new PortalMovesEvent(blue.getId(), blue.getXPos(), blue.getYPos(), chell.getId(), blue.getNormalX(), blue.getNormalY())));
        } else if (blue.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(blue.getId())));
        }
        PinTool &pinTool = chell.getPinTool();
        if (pinTool.switchedState()) {
            events.push_back(std::shared_ptr<Event>(new ObjectSwitchEvent(pinTool.getId())));
        }
        if (pinTool.changedPosition()) {
            events.push_back(std::shared_ptr<Event>(new ObjectMovesEvent(pinTool.getId(), pinTool.getXPos(), pinTool.getYPos())));
        }
    }
    for (Rock &rock : rocks) {
        if (rock.changedPosition()) {
            events.push_back(std::shared_ptr<Event>(new ObjectMovesEvent(rock.getId(), rock.getXPos(), rock.getYPos())));
        }
    }

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
