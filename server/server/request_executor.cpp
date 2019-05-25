//
// Created by franciscosicardi on 09/05/19.
//

#include <cstdint>
#include <iostream>
#include "protocol/protocol_code.h"
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
        connector >> instruction;
        if (instruction == new_game) {
            uint8_t map_id;
            connector >> map_id;
            gameManager.addGame(connector, map_id);
        } else if (instruction == join_game) {
            uint8_t game_id;
            connector >> game_id;
            gameManager.joinToGame(game_id, connector);
        } else {
            std::cerr << "Command not accepted: "
                      << (unsigned)instruction
                      << std::endl;
        }
    }
}

RequestExecutor::~RequestExecutor() = default;