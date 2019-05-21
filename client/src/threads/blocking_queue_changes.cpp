#include "blocking_queue_changes.h"

#include "../../../common/blocking_queue.h"
#include <memory>
#include "../common_texture/texture_move_change.h"
#include "game_object_action.h"

template class BlockingQueue<std::unique_ptr<TextureMoveChange>>;
template class BlockingQueue<std::pair<uint32_t, gameObjectAction_t>>;