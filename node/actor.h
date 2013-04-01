#ifndef __kawaii__node_actor__
#define __kawaii__node_actor__

#include "vector.h"
#include "hashed_string.h"
#include "node.h"

#include <memory>

namespace kawaii {

typedef unsigned int ActorId;
typedef HashedString ActorType;

class Actor : public Node {
public:
    static int NextId() {
        static int __last_id = 0;
        return ++__last_id;
    }

    Actor(const HashedString& t)
        : type_(t),
          id_(Actor::NextId()) {
    }

    virtual ~Actor() {}

    const ActorId id() const {
        return id_;
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