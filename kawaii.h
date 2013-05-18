#ifndef __kawaii__
#define __kawaii__

#include "kawaii/memory_pool.h"

#include "kawaii/application.h"
#include "kawaii/director.h"


#include "kawaii/types.h"
#include "kawaii/scheduler.h"
#include "kawaii/event_dispatcher.h"


#include "kawaii/assets_loader.h"
#include "kawaii/texture_2d.h"
#include "kawaii/texture_cache.h"
#include "kawaii/sprite_frame_cache.h"
#include "kawaii/animation_cache.h"
#include "kawaii/shader_cache.h"
#include "kawaii/animation_cache.h"

// node
#include "kawaii/node/scene.h"
#include "kawaii/node/layer.h"
#include "kawaii/node/sprite.h"
#include "kawaii/node/label_atlas.h"

// process
#include "kawaii/process/process_manager.h"
#include "kawaii/process/animate.h"
#include "kawaii/process/event_emit.h"
#include "kawaii/process/move_by.h"
#include "kawaii/process/move_to.h"
#include "kawaii/process/repeat.h"
#include "kawaii/process/sequence.h"
#include "kawaii/process/delay.h"

// structs
#include "kawaii/vector.h"
#include "kawaii/matrix.h"
#include "kawaii/vertices.h"

#include "kawaii/OpenGL_Internal.h"
#include "kawaii/drawing_primitives.h"

#include "kawaii/logger.h"

namespace kawaii {
}

#endif  /* defined(__kawaii__) */
