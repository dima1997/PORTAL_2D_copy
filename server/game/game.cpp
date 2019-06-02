//
// Created by franciscosicardi on 02/06/19.
//

#include <protocol/event/player_dies_event.h>
#include <protocol/game_action/coords_action.h>
#include <iostream>
#include <protocol/event/object_switch_event.h>
#include <portal_exception.h>
#include <protocol/event/player_wins_event.h>
#include "game.h"

#define TIME_WAIT_MICRO_SECONDS 10000
#define ONE_SECOND_EQ_MICRO_SECONDS 100000

void Game::start() {
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
                    std::shared_ptr<Event> ptrEvent(new PlayerDiesEvent());
//                    players.at(player_id).addToQueue(ptrEvent);
                    for (auto &player : players) {
                        if (player.getPlayerId() == player_id){
                            player.addToQueue(ptrEvent);
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
                    std::shared_ptr<Event> ptrEventHide(new ObjectSwitchEvent(idPortalAzul));
                    std::shared_ptr<Event> ptrEventMove(new ObjectMovesEvent(idPortalAzul, xMap, yMap));
                    std::shared_ptr<Event> ptrEventShow(new ObjectSwitchEvent(idPortalAzul));
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
                    std::shared_ptr<Event> ptrEventHide(new ObjectSwitchEvent(idPortalNaranja));
                    std::shared_ptr<Event> ptrEventMove(new ObjectMovesEvent(idPortalNaranja, xMap, yMap));
                    std::shared_ptr<Event> ptrEventShow(new ObjectSwitchEvent(idPortalNaranja));
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
        std::list<std::shared_ptr<ObjectMovesEvent>> moved;
        world.step(moved);
        for(auto &event : moved) {
            printf("x: %4.2f, y: %4.2f\n", event->getX(), event->getY());
            for (Player &player : players) {
                std::shared_ptr<Event> ptrEvent(event);
                player.addToQueue(ptrEvent);
            }
        }
        t1 = clock();
        double timeSpendMicroSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds((int)(timeWaitMicroSeconds - timeSpendMicroSeconds)));
    }

    for (Player &player : players) {
        std::shared_ptr<Event> ptrEvent(new PlayerWinsEvent());
        player.addToQueue(ptrEvent);
    }
}

Game::Game(std::vector<Connector> &connectors, Map &map): players(), thread(), numberOfPlayers(map.getPlayersNumber()), world(map), inQueue() {
    for (int i = 0; i < connectors.size(); ++i) {
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
    return numberOfPlayers == 0;
}
