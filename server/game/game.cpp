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
#include <protocol/event/player_dies_event.h>
#include "game.h"

#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>
#include <protocol/event/object_switch_event.h>
#include <memory>

#include <iostream>

#include "config_paths.h"
#include "yaml-cpp/yaml.h"

#define TIME_WAIT_MICRO_SECONDS 10000
#define ONE_SECOND_EQ_MICRO_SECONDS 100000 
#define SUMANDO_MAGICO 1000

Game &Game::operator=(Game &&other) noexcept {
    this->id = other.id;
    this->numberOfPlayers = other.numberOfPlayers;
    this->ready = other.ready;
    this->thread = std::move(other.thread);
    this->players = std::move(other.players);
    this->world = std::move(other.world);
    this->inQueue = std::move(inQueue);

    this->playerIds = std::move(other.playerIds);

    return *this;
}

Game::Game(Game &&other) noexcept: id(other.id), players(std::move(other.players)), mutex(), cv(),
                                   ready(other.ready), thread(std::move(other.thread)),
                                   numberOfPlayers(other.numberOfPlayers), world(std::move(other.world)),
                                   inQueue(std::move(other.inQueue)),
                                   playerIds(std::move(other.playerIds)) {
    for (auto &player : players) {
        player.setInQueue(&inQueue);
    }
}

Game::Game(uint8_t id, uint8_t map_id, Connector &connector): id(id), players(), mutex(), cv(), ready(false),
                                                              thread(), numberOfPlayers(), world(map_id),
                                                              playerIds() {
    numberOfPlayers = world.getNumberOfPlayers();
    YAML::Node baseNode = YAML::LoadFile(CONFIG_PATHS.at(map_id));
    YAML::Node chellsIds = baseNode["chells"]["id_coordinates"];
    for (int i = 0; i < (int)chellsIds.size(); ++i){
        this->playerIds.push_back(chellsIds[i]["id"].as<uint32_t>());
    }
    connector << (uint8_t) command_ok;
    connector << (uint8_t) id;
    std::unique_lock<std::mutex> l(mutex);
    uint32_t playerId = this->playerIds[0];
    connector << (uint32_t) playerId;
    Player player(playerId, connector, &inQueue); //0
    players.push_back(std::move(player));
}

bool Game::addPlayer(Connector &connector) {
    
    std::unique_lock<std::mutex> l(mutex);
    if (!ready) {
        connector << (uint8_t) command_ok;
        //uint32_t playerId = players.size();
        uint32_t playerId = this->playerIds[players.size()];
        connector << (uint8_t) playerId;
        Player player(playerId, connector, &inQueue);
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
    double timeWaitMicroSeconds = TIME_WAIT_MICRO_SECONDS;
    unsigned t0,t1,t2;
    while (numberOfPlayers > 0){
        t0 = clock();
        t2 = clock();
        double timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        while (timeProcessMicroSeconds <= timeWaitMicroSeconds && numberOfPlayers > 0) {
            std::unique_ptr<GameAction> ptrAction;
            if (!this->inQueue.pop(ptrAction)){
                break;
            }
            uint32_t player_id = ptrAction->getPlayerId();
            switch (ptrAction->getGameActionName()){
                case quit_game:
                    {
                        // player stop
                        --numberOfPlayers;
                        std::unique_ptr<Event> ptrEvent(new PlayerDiesEvent());
                        //players.at(player_id).addToQueue(ptrEvent);
                        for (auto &player : players) {
                            if (player.getPlayerId() == player_id){
                                player.setInQueue(&inQueue);
                            }
                        }
                    }
                    break;
                case move_left:
                    world.moveChellLeft(player_id);
                    break;
                case stop_left:
                    break;
                case move_right:
                    world.moveChellRight(player_id);
                    break;
                case stop_right:
                    break;
                case jump:
                    world.makeChellJump(player_id);
                    break;
                case stop_jump:
                    break;
                case open_blue_portal:
                    {
                        //Hago cosas con el portal azul
                        auto ptrAux = static_cast<CoordsAction *>(ptrAction.release());
                        std::unique_ptr<CoordsAction> ptrCoordsAction(ptrAux);
                        float xMap = ptrCoordsAction->getX();
                        float yMap = ptrCoordsAction->getY();
                        std::cout << "SERVER: Abriendo portal AZUL en x : "<< xMap << " y : " << yMap << "\n";
                        uint32_t idPortalAzul = player_id + 1; // hardcondeado
                        std::unique_ptr<Event> ptrEventHide(new ObjectSwitchEvent(idPortalAzul));
                        std::unique_ptr<Event> ptrEventMove(new ObjectMovesEvent(idPortalAzul, xMap, yMap));
                        std::unique_ptr<Event> ptrEventShow(new ObjectSwitchEvent(idPortalAzul));
                        for (auto &player : players) {
                            if (player.getPlayerId() == player_id){
                                player.addToQueue(ptrEventHide);
                                player.addToQueue(ptrEventMove);
                                player.addToQueue(ptrEventShow);
                            }
                        }
                        /*
                        players.at(player_id).addToQueue(ptrEventHide);
                        players.at(player_id).addToQueue(ptrEventMove);
                        players.at(player_id).addToQueue(ptrEventShow);
                        */
                    }
                    break;
                case open_orange_portal:
                    {
                        //Hago cosas con el portal naranja
                        auto ptrAux = static_cast<CoordsAction *>(ptrAction.release());
                        std::unique_ptr<CoordsAction> ptrCoordsAction(ptrAux);
                        float xMap = ptrCoordsAction->getX();
                        float yMap = ptrCoordsAction->getY();
                        std::cout << "SERVER: Abriendo portal NARANJA en x : "<< xMap << " y : " << yMap << "\n";
                        uint32_t idPortalNaranja = player_id + 2; // hardcondeado
                        std::unique_ptr<Event> ptrEventHide(new ObjectSwitchEvent(idPortalNaranja));
                        std::unique_ptr<Event> ptrEventMove(new ObjectMovesEvent(idPortalNaranja, xMap, yMap));
                        std::unique_ptr<Event> ptrEventShow(new ObjectSwitchEvent(idPortalNaranja));
                        for (auto &player : players) {
                            if (player.getPlayerId() == player_id){
                                player.addToQueue(ptrEventHide);
                                player.addToQueue(ptrEventMove);
                                player.addToQueue(ptrEventShow);
                            }
                        }
                        /*
                        players.at(player_id).addToQueue(ptrEventHide);
                        players.at(player_id).addToQueue(ptrEventMove);
                        players.at(player_id).addToQueue(ptrEventShow);
                        */
                    }
                    break;
                case pin_tool_on:
                    std::cout << "SERVER: pin tool on.\n";
                    break;
                case grab_it:
                    std::cout << "SERVER: grab it.\n";
                    break;
                case stop_grab:
                    std::cout << "SERVER: stop grab.\n";
                    break;
                case throw_it:
                    std::cout << "SERVER: throw it.\n";
                    break;
                case stop_throw:
                    std::cout << "SERVER: stop throw.\n";
                    break;
                case null_action:
                    break;
                default:
                    throw PortalException("Null action");
            }
            t2 = clock();
            timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        }
        std::list<ObjectMovesEvent *> moved;
        world.step(moved);
        for(auto event : moved) {
            printf("x: %4.2f, y: %4.2f\n", event->getX(), event->getY());
            for (Player &player : players) {
                std::unique_ptr<Event> ptrEvent(event);
                player.addToQueue(ptrEvent);
            }
        }
        t1 = clock();
        double timeSpendMicroSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds((int)(timeWaitMicroSeconds - timeSpendMicroSeconds)));
    }

    for (Player &player : players) {
        std::unique_ptr<Event> ptrEvent(new PlayerWinsEvent());
        player.addToQueue(ptrEvent);
    }
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
    for (auto &player : players) {
        player.join();
    }
}

bool Game::isFinished() {
    return numberOfPlayers == 0;
}
