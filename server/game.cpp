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
    return *this;
}

Game::Game(Game &&other) noexcept {
    this->id = other.id;
    this->numberOfPlayers = other.numberOfPlayers;
    this->ready = other.ready;
    this->finished = other.finished;
    this->thread = std::move(other.thread);
    this->players = std::move(other.players);
    std::condition_variable cv;

}

Game::Game(int id, Connector &connector): id(id), players(), mutex(), ready(false), finished(false), numberOfPlayers(3) {
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
    // start game logic (probably another class)
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body * groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef elementBodyDef;
    elementBodyDef.position.Set(-1.3f, 1.0f);
    b2Body * elementBody = world.CreateBody(&elementBodyDef);

    b2PolygonShape elementBox;
    elementBox.SetAsBox(1.0f, 1.0f);

    elementBody->CreateFixture(&elementBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body *body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    float32 timeStep = 1.0f / 60.0f;

    int32 velocityIterations = 8;
    int32 positionIterations = 2;


    printf("Game id: %d\n", id);
    for (int32 i = 0; i < 120; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float32  angle = body->GetAngle();
        printf("x: %4.2f, y: %4.2f, angle: %4.2f\n", position.x, position.y, angle);
    }
    printf("\n\n");

    for (Connector &player : players) {
        player << (uint8_t) 0;
    }
    std::unique_lock<std::mutex> l(mutex);
    finished = true;
}

// TODO: check thread
Game::~Game() = default;

void Game::startIfReady() {
    if (players.size() == numberOfPlayers && !ready) {
        ready = true;
        thread = std::thread(&Game::start, this);
    }
}

void Game::finish() {
    std::unique_lock<std::mutex> l(mutex);
    cv.wait(l, [this]{ return finished; });
}

bool Game::isFinished() {
    return finished;
}
