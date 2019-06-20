//
// Created by franciscosicardi on 29/04/19.
//
#include <blocking_queue.h>

#include <protocol/event/event.h>
#include <protocol/event/object_moves_event.h>
#include <connector/connector.h>
#include "blocking_queue.h"
#include "protocol/game_action/game_action.h"
#include <protocol/protocol_code.h>
#include <connector/connector.h>
#include <memory>

// To use this template just add here, for example:
template class BlockingQueue<Connector>;
template class BlockingQueue<std::shared_ptr<Event>>;
template class BlockingQueue<GameActionName>;
template class BlockingQueue<std::unique_ptr<GameAction>>;
template class BlockingQueue<std::unique_ptr<ObjectMovesEvent>>;
template class BlockingQueue<std::vector<char>>;

