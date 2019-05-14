//
// Created by franciscosicardi on 09/05/19.
//

#include "game.h"
#include "../common/protocol_code.h"

Game &Game::operator=(Game &&other) noexcept {
    return *this;
}

Game::Game(Game &&other) noexcept {
    this->id = other.id;
    this->numberOfPlayers = other.numberOfPlayers;
    this->ready = other.ready;
    this->players = std::move(other.players);
    other.players = std::vector<Connector>();
}

Game::Game(int id, Connector &connector): id(id), players(), mutex(), ready(false), numberOfPlayers(3) {
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
}

Game::~Game() {
//    if (ready) {
//        thread.join();
//    }
}

void Game::startIfReady() {
    if (players.size() == numberOfPlayers && !ready) {
        ready = true;
//            thread = std::thread(&Game::start, this);
    }
}
