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

#include <memory>

class Player {
private:
    uint32_t id;
    Connector connector;
    std::thread outThread;
    std::thread inThread;
    BlockingQueue<std::shared_ptr<Event>> outQueue;
    ThreadSafeQueue<std::unique_ptr<GameAction>> &inQueue;
    std::mutex mutex;
    bool recvMsgs;
    bool stillRecvMsgs();
    void stopRecv();
    void sendEvents();
    void recvGameActions();
public:
    Player(uint32_t id, Connector &connector, ThreadSafeQueue<std::unique_ptr<GameAction>> &inQueue);
    Player(Player &&other) noexcept;
    ~Player();
    void start();
    void join();
    void addToQueue(std::shared_ptr<Event> &ptrEvent);
    uint32_t getPlayerId();
};


#endif //PORTAL_PLAYER_H
