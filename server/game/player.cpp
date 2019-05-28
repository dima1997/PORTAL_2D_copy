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
    Event *event;
    while (outQueue.pop(event)) {
        switch (event->eventType) {
            case object_moves:
                connector << *(ObjectMovesEvent *) event;
                break;
            case player_wins:
                connector << *(PlayerWinsEvent *) event;
                break;
            case player_dies:
                connector << *(PlayerDiesEvent *) event;
                break;
            case object_switch_state:
            default:
                throw PortalException("Command unknown");
        }
        delete event;
    }
}

void Player::recvGameActions() {
    //auto *gameAction = new GameAction();
    while (stillRecvMsgs()) {
        uint8_t actionNameExplicit;
        //connector >> *gameAction;
        connector >> actionNameExplicit;
        GameActionName actionName = (GameActionName) actionNameExplicit;
        std::unique_ptr<GameAction> ptrAction;
        switch(actionName){
            case open_blue_portal:
            case open_orange_portal:
                {
                    ptrAction.reset(new CoordsAction(actionName));
                    connector >> (*ptrAction);
                }
                break;
            default:
                {
                    ptrAction.reset(new GameAction(actionName));
                }
                break;
        }
        //gameAction->setPlayerId(id);
        //inQueue->push(gameAction);
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

void Player::addToQueue(Event *event) {
    outQueue.push(event);
}

//void Player::setInQueue(ThreadSafeQueue<GameAction *> *inQueue) {
void Player::setInQueue(ThreadSafeQueue<std::unique_ptr<GameAction>> * inQueue) {
    this->inQueue = inQueue;
}

Player::~Player() = default;
