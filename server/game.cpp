//
// Created by franciscosicardi on 09/05/19.
//

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "game.h"
#include "../common/protocol_code.h"

Game &Game::operator=(Game &&other) noexcept {
    this->id = other.id;
    this->numberOfPlayers = other.numberOfPlayers;
    this->ready = other.ready;
    this->finished = other.finished;
    this->thread = std::move(other.thread);
    this->players = std::move(other.players);
    this->world = std::move(other.world);
    return *this;
}

Game::Game(Game &&other) noexcept: id(other.id), players(std::move(other.players)), mutex(), cv(),
                                   ready(other.ready), finished(other.finished), thread(std::move(other.thread)),
                                   numberOfPlayers(other.numberOfPlayers), world(std::move(other.world)) {
}

Game::Game(uint8_t id, uint8_t map_id, Connector &connector): id(id), players(), mutex(), cv(), ready(false),
                                                              finished(false), thread(), numberOfPlayers(3),
                                                              world(map_id) {
    connector << command_ok;
    connector << id;
    players.push_back(std::move(connector));
}

bool Game::addPlayer(Connector &connector) {
    std::unique_lock<std::mutex> l(mutex);
    if (!ready) {
        connector << command_ok;
        connector << (uint8_t) players.size(); // player id
        players.push_back(std::move(connector));
        return true;
    }
    return false;

}

void Game::start() {
    printf("Game id: %d\n", id);
    std::list<b2Body *> updated;
    for (int32 i = 0; i < 60; ++i) {
        world.step(updated);
        for(auto *body : updated) {
            b2Vec2 position = body->GetPosition();
            printf("x: %4.2f, y: %4.2f\n", position.x, position.y);
        }
    }
    printf("\n\n");

    for (Connector &player : players) {
        player << (uint8_t) 0;
    }
    std::unique_lock<std::mutex> l(mutex);
    finished = true;
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
    return finished;
}
