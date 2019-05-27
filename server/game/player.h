//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_PLAYER_H
#define PORTAL_PLAYER_H


#include <thread>
#include <mutex>
#include <protocol/event/event.h>
#include <connector/connector.h>
#include <protocol/game_action/game_action.h>
#include <thread_safe_queue.h>
#include <blocking_queue.h>

class Player {
private:
    uint32_t id;
    Connector connector;
    std::thread outThread;
    std::thread inThread;
    BlockingQueue<Event *> outQueue;
    ThreadSafeQueue<GameAction *> *inQueue;
    std::mutex mutex;
    bool recvMsgs;
    bool stillRecvMsgs();
    void stopRecv();
    void sendEvents();
    void recvGameActions();
public:
    Player(uint32_t id, Connector &connector, ThreadSafeQueue<GameAction *> *inQueue);
    Player(Player &&other) noexcept;
    ~Player();
    void start();
    void join();
    void addToQueue(Event *event);
    void setInQueue(ThreadSafeQueue<GameAction *> *inQueue);
};


#endif //PORTAL_PLAYER_H
