#include <thread_safe_queue.h>

#include "../../includes/textures/common_texture/texture_change.h"

template class ThreadSafeQueue<std::unique_ptr<TextureChange>>;
