//
// Created by franciscosicardi on 21/05/19.
//

#include "player.h"
#include <protocol/object_moves_event.h>
#include <portal_exception.h>

Player::Player(Connector &connector, BlockingQueue<GameAction *> &inQueue):
               connector(std::move(connector)), outThread(), inThread(),
               outQueue(), inQueue(inQueue), recvMsgs(true) {}

void Player::join() {
    stopRecv();
    inThread.join();
    outQueue.close();
    outThread.join();
}

void Player::sendEvents() {
    Event *event;
    while (outQueue.pop(event)) {
        switch (event->eventType) {
            case object_moves:
                connector << *(ObjectMovesEvent *) event;
                break;
            case player_wins:
            case player_dies:
            case object_switch_state:
            default:
                throw PortalException("Command unknown");
        }
        delete event;
    }
}

void Player::recvGameActions() {
    auto *gameAction = new GameAction();
    while (stillRecvMsgs()) {
        connector >> *gameAction;
        inQueue.push(gameAction);
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

Player::Player(Player &&other) noexcept : connector(std::move(other.connector)), outThread(std::move(other.outThread)),
                                inThread(std::move(other.inThread)), outQueue(std::move(other.outQueue)),
                                inQueue(other.inQueue), mutex(), recvMsgs(other.recvMsgs) {}

void Player::addToQueue(Event *event) {
    outQueue.push(event);
}

Player::~Player() = default;
