//
// Created by franciscosicardi on 09/05/19.
//

#include <cstdint>
#include <iostream>
#include <protocol/protocol_code.h>
#include "request_executor.h"

RequestExecutor::RequestExecutor(BlockingQueue<Connector> &queue,
                                 GameManager &gameManager):
        queue(queue), gameManager(gameManager) {}

void RequestExecutor::operator()() {
    thread = std::thread(&RequestExecutor::execute, this);
}

void RequestExecutor::join() {
    thread.join();
}

void RequestExecutor::execute() {
    Connector connector;
    while (queue.pop(connector)) {
        uint8_t instruction;
        try {
            connector >> instruction;
        } catch(SocketException &se) {
            std::cerr << se.what() << std::endl;
            continue;
        }
        if (instruction == new_game) {
            gameManager.addGame(connector);
        } else if (instruction == join_game) {
            gameManager.joinToGame(connector);
        } else {
            std::cerr << "Command not accepted: "
                      << (unsigned)instruction
                      << std::endl;
        }
    }
}

RequestExecutor::~RequestExecutor() = default;