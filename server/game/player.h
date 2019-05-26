//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_PLAYER_H
#define PORTAL_PLAYER_H


#include <thread>
#include <mutex>
#include <blocking_queue.h>
#include <protocol/event.h>
#include <connector/connector.h>
#include <game_action.h>

class Player {
private:
    Connector connector;
    std::thread outThread;
    std::thread inThread;
    BlockingQueue<Event *> outQueue;
    BlockingQueue<GameAction *> &inQueue;
    std::mutex mutex;
    bool recvMsgs;
    bool stillRecvMsgs();
    void stopRecv();
    void sendEvents();
    void recvGameActions();
public:
    Player(Connector &connector, BlockingQueue<GameAction *> &inQueue);
    Player(Player &&other) noexcept;
    ~Player();
    void start();
    void join();
    void addToQueue(Event *event);
};


#endif //PORTAL_PLAYER_H
