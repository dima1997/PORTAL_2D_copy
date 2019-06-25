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
#include "client_action/client_action.h"

typedef enum player_state {WAITING_P, RECEIVING_P, FINISHED_P, ERROR_P} player_state_t;

class Player {
private:
    uint32_t id;
    Connector connector;
    std::thread outThread;
    std::thread inThread;
    BlockingQueue<std::shared_ptr<Event>> outQueue;
    ThreadSafeQueue<std::unique_ptr<ClientAction>> &inQueue;
    std::mutex mutex;
    player_state_t state;
    void setState(player_state_t state);
    void sendEvents();
    void recvGameActions();
    void start();
public:
    Player(uint32_t id, Connector &connector, ThreadSafeQueue<std::unique_ptr<ClientAction>> &inQueue);
    Player(Player &&other) noexcept;
    ~Player();
    bool stillRecvMsgs();
    void join();
    void addToQueue(std::shared_ptr<Event> &ptrEvent);
    player_state_t getState();
};


#endif //PORTAL_PLAYER_H
