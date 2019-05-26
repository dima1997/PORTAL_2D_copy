//
// Created by franciscosicardi on 09/05/19.
//

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <protocol/protocol_code.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/player_wins_event.h>
#include <portal_exception.h>
#include <chrono>
#include "game.h"

#define TIME_WAIT_MILI_SECONDS 75

Game &Game::operator=(Game &&other) noexcept {
    this->id = other.id;
    this->numberOfPlayers = other.numberOfPlayers;
    this->ready = other.ready;
    this->alivePlayers = other.alivePlayers;
    this->thread = std::move(other.thread);
    this->players = std::move(other.players);
    this->world = std::move(other.world);
    return *this;
}

Game::Game(Game &&other) noexcept: id(other.id), players(std::move(other.players)), mutex(), cv(),
                                   ready(other.ready), alivePlayers(other.alivePlayers), thread(std::move(other.thread)),
                                   numberOfPlayers(other.numberOfPlayers), world(std::move(other.world)),
                                   inQueue(std::move(other.inQueue)) {}

Game::Game(uint8_t id, uint8_t map_id, Connector &connector): id(id), players(), mutex(), cv(), ready(false),
                                                              alivePlayers(3), thread(), numberOfPlayers(3),
                                                              world(map_id) {
    connector << (uint8_t) command_ok;
    connector << (uint8_t) id;
    std::unique_lock<std::mutex> l(mutex);
    Player player(0, connector, inQueue);
    players.push_back(std::move(player));
}

bool Game::addPlayer(Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    if (!ready) {
        connector << (uint8_t) command_ok;
        uint32_t playerId = players.size();
        connector << (uint8_t) playerId;
        Player player(playerId, connector, inQueue);
        players.push_back(std::move(player));
        return true;
    }
    return false;

}

void Game::start() {
    printf("Game id: %d\n", id);
    for(auto &player : players) {
        player.start();
    }
    double timeWaitMiliSeconds = TIME_WAIT_MILI_SECONDS;
    unsigned t0,t1,t2;
    while (alivePlayers > 0){
        t0 = clock();
        t2 = clock();
        double timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        while (timeProcessMiliSeconds <= timeWaitMiliSeconds && alivePlayers > 0){
            GameAction *action;
            if (!this->inQueue.pop(action)){
                break;
            }
            switch (action->getGameActionName()){
                case move_left:
                    // move_left
                    break;
                case move_right:
                    // move_right
                    break;
                case quit_game:
                    // player stop
                    --alivePlayers;
                    break;
                case null_action:
                default:
                    throw PortalException("Null action");
            }
            t2 = clock();
            timeProcessMiliSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * 1000;
        }
        std::list<ObjectMovesEvent> moved;
        for (int32 i = 0; i < 60; ++i) {
            world.step(moved);
            for(auto &event : moved) {
                printf("x: %4.2f, y: %4.2f\n", event.getX(), event.getY());
                for (Player &player : players) {
                    player.addToQueue(&event);
                }
            }
            moved.clear();
        }
        printf("\n\n");
        t1 = clock();
        double timeSpendMiliSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(timeWaitMiliSeconds - timeSpendMiliSeconds)));
    }

    for (Player &player : players) {
        player.addToQueue(new PlayerWinsEvent());
    }
    std::unique_lock<std::mutex> l(mutex);
}

Game::~Game() = default;

void Game::startIfReady() {
    std::unique_lock<std::mutex> l(mutex);
    if (players.size() == numberOfPlayers && !ready) {
        ready = true;
        thread = std::thread(&Game::start, this);
    }
}

void Game::join() {
    thread.join();
}

bool Game::isFinished() {
    return alivePlayers > 0;
}
