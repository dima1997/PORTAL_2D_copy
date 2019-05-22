#ifndef QUEUE_CHANGES_H
#define QUEUE_CHANGES_H

#include <queue>
#include "../common_texture/texture_move_change.h"

enum gameObjectAction_t : uint32_t {
    MOVE_LEFT,
    MOVE_RIGHT
};

typedef queue<std::pair<uint32_t, std::unique_ptr<TextureMoveChange>>> queueChangesMade_t;
typedef queue<std::pair<uint32_t, gameObjectAction_t>>> queueChangesAsk_t;

#endif // QUEUE_CHANGES_H