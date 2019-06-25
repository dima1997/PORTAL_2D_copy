//
// Created by franciscosicardi on 02/06/19.
//

#include <protocol/event/player_dies_event.h>
#include <protocol/game_action/coords_action.h>
#include <iostream>
#include <protocol/event/object_switch_event.h>
#include <portal_exception.h>
#include <protocol/event/player_wins_event.h>
#include <protocol/event/game_starts_event.h>
#include "game.h"
#include "../config/global_configuration.h"

#define ONE_SECOND_EQ_MICRO_SECONDS 100000

void Game::start() {
    gameState = PLAYING;
    for(auto &player : players) {
        auto event = std::shared_ptr<Event>(new GameStartsEvent());
        player.addToQueue(event);
    }
    // this to make time for the last window to load
    std::this_thread::sleep_for(std::chrono::seconds(CONFIG.waitBeforeStartSeconds));
    unsigned t0,t1,t2;
    while (true){
        t0 = clock();
        t2 = clock();
        double timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        while (timeProcessMicroSeconds <= CONFIG.stepMaxTimeMicroSeconds && !world.hasFinished()) {
            std::unique_ptr<ClientAction> ptrAction;
            if (!this->inQueue.pop(ptrAction)){
                break;
            }
            ptrAction->execute(world);
            t2 = clock();
            timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        }
        std::list<std::shared_ptr<Event>> events;
        world.step(events);
        for(auto &event : events) {
            for (Player &player : players) {
                std::shared_ptr<Event> ptrEvent(event);
                player.addToQueue(ptrEvent);
            }
        }
        if (world.hasFinished()) break;
        t1 = clock();
        double timeSpendMicroSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds((int)(CONFIG.stepMaxTimeMicroSeconds - timeSpendMicroSeconds)));
    }
    gameState = FINISHED;
}

Game::Game(Connector &connector, uint8_t mapId): players(), thread(), map(mapId), world(map), inQueue(), gameState(WAITING) {
    uint32_t playerId = map.getPlayerId(0);
    connector << (uint32_t) playerId;
    connector << map.toString();
    players.emplace_back(playerId, connector, inQueue);
    if (readyToStart()) gameState = READY;
}

void Game::operator()() {
    thread = std::thread(&Game::start, this);
}

void Game::join() {
    if (thread.joinable()) {
        thread.join();
    }
    for (auto &player : players) {
        player.join();
    }
}

Game::~Game() = default;

void Game::addPlayer(Connector &connector) {
    uint32_t playerId = map.getPlayerId(getNumberOfPlayers());
    connector << playerId;
    connector << map.toString();
    players.emplace_back(playerId, connector, inQueue);
    if (readyToStart()) gameState = READY;
}

uint8_t Game::getNumberOfPlayers() {
    auto it = players.begin();
    while (it != players.end()) {
        if (!(*it).stillRecvMsgs()) {
            (*it).join();
            it = players.erase(it);
        } else {
            ++it;
        }
    }
    return players.size();
}

bool Game::readyToStart() {
    return getNumberOfPlayers() == map.getPlayersNumber();
}

game_state_t Game::getState() {
    return gameState;
}
