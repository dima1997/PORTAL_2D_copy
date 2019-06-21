#include "thread_safe_queue.h"

#include <protocol/protocol_code.h>

#include <memory>
#include <protocol/game_action/game_action.h>
#include <protocol/event/object_moves_event.h>

template class ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>>;
template class ThreadSafeQueue<std::unique_ptr<Event>>;
template class ThreadSafeQueue<std::unique_ptr<GameAction>>;
template class ThreadSafeQueue<GameActionName>;
template class ThreadSafeQueue<ThreadStatus>;

