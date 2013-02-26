#ifndef __kawaii__event_dispatcher__
#define __kawaii__event_dispatcher__

#include "hashed_string.h"
#include "types.h"
#include "memory_pool.h"

#include <memory>
#include <list>
#include <map>
#include <ctime>

namespace kawaii {
using namespace std;

typedef HashedString EventType;

typedef enum {
    kScriptDefined,             // Event is defined in script.
    kCodeEventOnly,             // Event is defined by main code, and is NOT callable from script.
    kCodeEventScriptCallable,   // Event is defined by code, but is callable from script.
} EventCallable;

struct EventTypeMetadata {
    explicit EventTypeMetadata(EventCallable c) : callable(c) {}
    EventCallable callable;
};

struct Event : public GeneralPoolable {
public:
    Event(const EventType t) : type(t) {
        timestamp = std::time(NULL);
    }

    EventType type;
    time_t timestamp;
};

class EventListenerInterface {
public:
    virtual ~EventListenerInterface() {}
    virtual bool HandleEvent(shared_ptr<Event> e) = 0;
};

class EventDispatcher {
public:
    // typedef std::map<EventType, EventTypeMetadata> EventTypeTable;
    typedef std::multimap<EventType, EventListenerInterface *> EventListenerTable;

    EventDispatcher() :
        active_queue_index_(0) {
    }

    bool On(const EventType& type, EventListenerInterface *listener);
    bool Off(const EventType& type);
    bool Off(EventListenerInterface *listener);
    bool Trigger(shared_ptr<Event> event);
    bool Queue(shared_ptr<Event> event);
    bool Tick(const ii_time max_time);

private:
    bool IsValidType(const EventType& type) const;
    bool IsListerningType(const EventType& type) const;

    enum {
        NUM_QUEUES = 2
    };

    list<shared_ptr<Event> > queues_[NUM_QUEUES];
    int active_queue_index_;

    // EventTypeTable types_;
    EventListenerTable listeners_;
};

}

#endif /* defined(__kawaii__event_dispacher__) */

