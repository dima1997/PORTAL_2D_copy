//
// Created by franciscosicardi on 21/05/19.
//

#include "player.h"
#include "../common/protocol/object_moves_event.h"

Player::Player(Connector connector, BlockingQueue<Event *> &inQueue):
               connector(std::move(connector)), outThread(), inThread(),
               outQueue(), inQueue(inQueue) {}

void Player::join() {
    inThread.join();
    outThread.join();
}

void Player::sendEvents() {
    Event *event;
    while (outQueue.pop(event)) {
        EventType type = event->eventType;
        if (type == object_moves) {
            connector << *(ObjectMovesEvent *) event;
        } else if (type == player_wins) {
            // send data
        }
    }
}

Player::~Player() = default;
