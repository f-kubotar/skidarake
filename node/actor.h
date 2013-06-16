#ifndef __kawaii__node_actor__
#define __kawaii__node_actor__

#include "kawaii/vector.h"
#include "kawaii/hashed_string.h"
#include "kawaii/node/node.h"
#include "kawaii/actor_id.h"

#include <memory>

#include <uuid/uuid.h>

namespace kawaii {

typedef HashedString ActorType;

class Actor : public Node {
public:
    Actor(const HashedString& t)
        : type_(t),
          id_() {
    }

    virtual ~Actor() {}

    const ActorId& id() const {
        return id_;
    }

    void *id_ptr() {
        return static_cast<void *>(&id_);
    }

    const HashedString type() const {
        return type_;
    }

protected:
    ActorId id_;
    HashedString type_;
};

}

#endif /* defined(__kawaii__node_actor__) */
