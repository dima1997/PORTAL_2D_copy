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

#define SECONDS_WAIT_BEFORE_START 2
#define TIME_WAIT_MICRO_SECONDS 10000
#define ONE_SECOND_EQ_MICRO_SECONDS 100000

void Game::start() {
    for(auto &player : players) {
        player.start();
        auto event = std::shared_ptr<Event>(new GameStartsEvent());
        player.addToQueue(event);
    }
    // this to make time for the last window to load
    std::this_thread::sleep_for(std::chrono::seconds(SECONDS_WAIT_BEFORE_START));
    double timeWaitMicroSeconds = TIME_WAIT_MICRO_SECONDS;
    unsigned t0,t1,t2;
    while (true){
        t0 = clock();
        t2 = clock();
        double timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        while (timeProcessMicroSeconds <= timeWaitMicroSeconds && !world.hasFinished()) {
            std::unique_ptr<GameAction> ptrAction;
            if (!this->inQueue.pop(ptrAction)){
                break;
            }
            manageActions(std::move(ptrAction));
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
        std::this_thread::sleep_for(std::chrono::microseconds((int)(timeWaitMicroSeconds - timeSpendMicroSeconds)));
    }
    finished = true;
}

void Game::manageActions(std::unique_ptr<GameAction> ptrAction) {
    uint32_t player_id = ptrAction->getPlayerId();
    switch (ptrAction->getGameActionName()){
        case quit_game:
            world.getChell(player_id).die();
            break;
        case move_left:
            world.getChell(player_id).updateState(LEFT);
            break;
        case move_right:
            world.getChell(player_id).updateState(RIGHT);
            break;
        case stop_move:
            world.getChell(player_id).updateState(STOP);
            break;
        case jump:
            world.getChell(player_id).updateState(JUMP);
            break;
        case open_blue_portal:
        {
            auto ptrAux = dynamic_cast<CoordsAction *>(ptrAction.release());
            std::unique_ptr<CoordsAction> ptrCoordsAction(ptrAux);
            float xMap = ptrCoordsAction->getX();
            float yMap = ptrCoordsAction->getY();
            std::cout << "SERVER: Abriendo portal AZUL en x : "<< xMap << " y : " << yMap << "\n";
            world.getChell(player_id).shootPortal(xMap, yMap, BLUE);
        }
            break;
        case open_orange_portal:
        {
            auto ptrAux = dynamic_cast<CoordsAction *>(ptrAction.release());
            std::unique_ptr<CoordsAction> ptrCoordsAction(ptrAux);
            float xMap = ptrCoordsAction->getX();
            float yMap = ptrCoordsAction->getY();
            std::cout << "SERVER: Abriendo portal NARANJA en x : "<< xMap << " y : " << yMap << "\n";
            world.getChell(player_id).shootPortal(xMap, yMap, ORANGE);
        }
            break;
        case pin_tool_on:
            std::cout << "SERVER: pin tool on.\n";
            break;
        case grab_it:
            world.getChell(player_id).grabRock();
            break;
        case throw_right:
            world.getChell(player_id).throwRock(THROW_RIGHT);
            break;
        case throw_left:
            world.getChell(player_id).throwRock(THROW_LEFT);
            break;
        case reset_portals:
            std::cout << "SERVER: reset portals.\n";
            break;
        case kill:
            std::cout << "SERVER: kill player.\n";
            break;
        case null_action:
            break;
        default:
            throw PortalException("Null action");
    }
}

Game::Game(std::vector<Connector> &connectors, Map &map): players(), thread(), world(map), inQueue(), finished(false) {
    for (int i = 0; i < (int)connectors.size(); ++i) {
        auto playerId = map.getPlayerId(i);
        Connector &connector = connectors[i];
        players.emplace_back(playerId, connector, inQueue);
    }
}

void Game::operator()() {
    thread = std::thread(&Game::start, this);
}

void Game::join() {
    thread.join();
    for (auto &player : players) {
        player.join();
    }
}

bool Game::isFinished() {
    return finished;
}

Game::~Game() {
    this->join();
}
