#ifndef __kawaii__node_layer__
#define __kawaii__node_layer__

#include "kawaii/actor_id.h"
#include "kawaii/logger.h"
#include "kawaii/node/node.h"

#include <unordered_map>

namespace kawaii {
using namespace std;

typedef unordered_map<ActorId, weak_ptr<Node>, ActorIdHash> ActorNodeTable;

class Layer : public Node {
public:
    Layer();

    virtual ~Layer() {}

    virtual bool Init() { return true; }

    virtual void AddChild(shared_ptr<Node> child) {
        Node::AddChild(child);

        const ActorId& actor_id = child->actor_id();
        if (!actor_id.is_null()) {
            //ActorNodeTable::iterator i = actor_node_table_.find(actor_id);
            actor_node_table_[actor_id] = child;
        }
    }

    virtual void RemoveChild(shared_ptr<Node> child) {
        Node::RemoveChild(child);

        const ActorId& actor_id = child->actor_id();
        if (!actor_id.is_null()) {
            ActorNodeTable::iterator i = actor_node_table_.find(actor_id);
            if (i != actor_node_table_.end()) {
                actor_node_table_.erase(i);
            }
        }
    }

    virtual void RemoveChild(const ActorId& id) {
        ActorNodeTable::iterator i = actor_node_table_.find(id);
        if (i != actor_node_table_.end()) {
            if (shared_ptr<Node> node = i->second.lock()) {
                Node::RemoveChild(node);
            }
            actor_node_table_.erase(i);
        }
    }

    shared_ptr<Node> FindNodeByActorId(const ActorId& id);
    
    shared_ptr<Node> operator[](const ActorId& id) {
        return FindNodeByActorId(id);
    }

protected:
    ActorNodeTable actor_node_table_;
};

}

#endif /* defined(__kawaii__node_layer__) */
