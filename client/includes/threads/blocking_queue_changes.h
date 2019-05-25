#ifndef BLOCKING_QUEUE_CHANGES_H
#define BLOCKING_QUEUE_CHANGES_H

#include "../../../common/blocking_queue.h"
#include "../common_texture/texture_move_change.h"

#include <memory>
#include <cstdint>

enum gameObjectAction_t : uint32_t {
    MOVE_LEFT,
    MOVE_RIGHT
};

typedef BlockingQueue<std::unique_ptr<TextureMoveChange>> 
blockingQueueChangesMade_t;

typedef BlockingQueue<std::pair<uint32_t, gameObjectAction_t>> 
blockingQueueChangesAsk_t;

#endif // BLOCKING_QUEUE_CHANGES_H