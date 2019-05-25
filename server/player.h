//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_PLAYER_H
#define PORTAL_PLAYER_H


#include <thread>
#include "../common/blocking_queue.h"
#include "../common/protocol/event.h"
#include "../common/connector/connector.h"

class Player {
private:
    Connector connector;
    std::thread outThread;
    std::thread inThread;
    BlockingQueue<Event *> outQueue;
    BlockingQueue<Event *> &inQueue;
public:
    Player(Connector connector, BlockingQueue<Event *> &inQueue);
    ~Player();
    void join();
    void sendEvents();
};


#endif //PORTAL_PLAYER_H
