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

//Player::Player(uint32_t id, Connector &connector, ThreadSafeQueue<GameAction *> *inQueue):
Player::Player(uint32_t id, Connector &connector, 
                ThreadSafeQueue<std::unique_ptr<GameAction>> * inQueue) :
               id(id), connector(std::move(connector)), outThread(), inThread(),
               outQueue(), inQueue(inQueue), recvMsgs(true) {}

void Player::join() {
    stopRecv();
    inThread.join();
    outQueue.close();
    outThread.join();
}

void Player::sendEvents() {
    std::unique_ptr<Event> ptrEvent;
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
        connector >> actionNameExplicit;
        auto actionName = (GameActionName) actionNameExplicit;
        std::unique_ptr<GameAction> ptrAction;
        switch(actionName){
            case open_blue_portal:
            case open_orange_portal:
                ptrAction = std::make_unique<CoordsAction>(actionName);
                connector >> *ptrAction;
                break;
            case quit_game:
                stopRecv();
            default:
                ptrAction = std::make_unique<GameAction>(actionName);
                break;
        }
        ptrAction->setPlayerId(id);
        inQueue->push(ptrAction);
    }
}

bool Player::stillRecvMsgs() {
    std::unique_lock<std::mutex> l(mutex);
    return recvMsgs;
}

void Player::stopRecv() {
    std::unique_lock<std::mutex> l(mutex);
    recvMsgs = false;
}

void Player::start() {
    outThread = std::thread(&Player::sendEvents, this);
    inThread = std::thread(&Player::recvGameActions, this);
}

Player::Player(Player &&other) noexcept : id(other.id), connector(std::move(other.connector)), outThread(std::move(other.outThread)),
                                inThread(std::move(other.inThread)), outQueue(std::move(other.outQueue)),
                                inQueue(other.inQueue), mutex(), recvMsgs(other.recvMsgs) {}

void Player::addToQueue(std::unique_ptr<Event> & ptrEvent) {
    outQueue.push(ptrEvent);
}

void Player::setInQueue(ThreadSafeQueue<std::unique_ptr<GameAction>> *_inQueue) {
    this->inQueue = _inQueue;
}

Player::~Player() = default;
