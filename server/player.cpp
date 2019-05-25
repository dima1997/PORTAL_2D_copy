//
// Created by franciscosicardi on 21/05/19.
//

#include "player.h"
#include "../common/protocol/object_moves_event.h"
#include "../common/portal_exception.h"

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
    }
}

Player::~Player() = default;
