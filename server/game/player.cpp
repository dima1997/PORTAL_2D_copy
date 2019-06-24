#include <memory>

#include <memory>

//
// Created by franciscosicardi on 21/05/19.
//

#include "player.h"
#include <protocol/event/object_moves_event.h>
#include <portal_exception.h>
#include <protocol/event/player_dies_event.h>
#include <protocol/event/player_wins_event.h>

#include <protocol/game_action/game_action.h>
#include <protocol/game_action/coords_action.h>

#include <memory>
#include <err.h>
#include <iostream>

Player::Player(uint32_t id, Connector &connector,
                ThreadSafeQueue<std::unique_ptr<GameAction>> &inQueue) :
               id(id), connector(std::move(connector)), outThread(), inThread(),
               outQueue(), inQueue(inQueue), mutex(), state(WAITING_P) {
    start();
}

void Player::join() {
    setState(FINISHED_P);
    connector.shutDownRD();
    inThread.join();
    outQueue.close();
    connector.shutDownWR();
    outThread.join();
}

void Player::sendEvents() {
    std::shared_ptr<Event> ptrEvent;
    while (outQueue.pop(ptrEvent)) {
        try {
            connector << (*ptrEvent);
        } catch (SocketException &e) {
            outQueue.close();
        }
    }
}

void Player::recvGameActions() {
    while (stillRecvMsgs()) {
        uint8_t actionNameExplicit;
        try {
            connector >> actionNameExplicit;
            if (getState() == WAITING_P) {
                setState(ERROR_P);
                return;
            }
            auto actionName = (GameActionName) actionNameExplicit;
            std::unique_ptr<GameAction> ptrAction;
            switch(actionName){
                case open_blue_portal:
                case open_orange_portal:
                case pin_tool_on:
                    ptrAction = std::unique_ptr<CoordsAction>(new CoordsAction(actionName));
                    connector >> *ptrAction;
                    break;
                case quit_game:
                    setState(FINISHED_P);
                default:
                    ptrAction = std::unique_ptr<GameAction>(new GameAction(actionName));
                    break;
            }
            ptrAction->setPlayerId(id);
            inQueue.push(ptrAction);
        } catch (SocketException &e) {
            setState(ERROR_P);

        }
    }
}

bool Player::stillRecvMsgs() {
    std::unique_lock<std::mutex> l(mutex);
    return state == WAITING_P || state == RECEIVING_P;
}

void Player::setState(player_state_t state) {
    std::unique_lock<std::mutex> l(mutex);
    this->state = state;
}

void Player::start() {
    outThread = std::thread(&Player::sendEvents, this);
    inThread = std::thread(&Player::recvGameActions, this);
    setState(RECEIVING_P);
}

Player::Player(Player &&other) noexcept : id(other.id), connector(std::move(other.connector)), outThread(std::move(other.outThread)),
                                inThread(std::move(other.inThread)), outQueue(std::move(other.outQueue)),
                                inQueue(other.inQueue), mutex(), state(other.state) {}

void Player::addToQueue(std::shared_ptr<Event> &ptrEvent) {
    outQueue.push(ptrEvent);
}

player_state_t Player::getState() {
    std::unique_lock<std::mutex> l(mutex);
    return state;
}

Player::~Player() = default;
