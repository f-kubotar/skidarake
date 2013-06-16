#ifndef __kawaii__actor_id__
#define __kawaii__actor_id__

#include "kawaii/memory_pool.h"

#include <string>
#include <memory>
#include <functional>

#include <uuid/uuid.h>
#include <cstdlib>

using namespace std;

namespace kawaii {

class ActorId {
public:
    ActorId() {
        uuid_ptr_ = static_cast<unsigned char *>(GeneralMemoryPool::Shared()->Alloc(sizeof(uuid_t)));
    }
    
    ~ActorId() {
        GeneralMemoryPool::Shared()->Free(uuid_ptr_, sizeof(uuid_t));
    }

    ActorId(const ActorId& rhs) {
        uuid_ptr_ = static_cast<unsigned char *>(GeneralMemoryPool::Shared()->Alloc(sizeof(uuid_t)));
        uuid_copy(uuid_ptr_, rhs.uuid_ptr());
    }

    void Generate() {
        uuid_generate(uuid_ptr_);
    }

    const string str() const {
        char buf[37];
        uuid_unparse(uuid_ptr_, buf);
        return string(buf);
    }
    
    const unsigned char *uuid_ptr() const {
        return uuid_ptr_;
    }

    const char *c_str() const {
        return str().c_str();
    }

    bool is_null() {
        return uuid_is_null(uuid_ptr_);
    }

    ActorId& operator=(const ActorId& rhs) {
        uuid_copy(uuid_ptr_, rhs.uuid_ptr());
        return (*this);
    }

    bool operator==(const ActorId& rhs) const {
        return (uuid_compare(uuid_ptr_, rhs.uuid_ptr()) == 0);
    }

private:
    unsigned char *uuid_ptr_;
};

struct ActorIdHash : public unary_function<ActorId, size_t> {
    size_t operator()(const ActorId& value) const {
        std::hash<string> hash;
        return hash(value.str());
    }
};

}

#endif /* defined(__kawaii__actor_id__) */
