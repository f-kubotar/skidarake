#ifndef __kawaii__process_event_emit__
#define __kawaii__process_event_emit__

#include "event_dispatcher.h"

#include "application.h"

namespace kawaii {

class EventEmit : public Process {
public:
    static const HashedString TYPE;

    EventEmit(shared_ptr<Event> event)
        : event_(event){}

    const HashedString& type() const {
        return TYPE;
    }

    virtual bool Update(const ii_time delta) {
        Application::Instance().director().dispatcher().Queue(event_);
        return false;
    }

private:
    shared_ptr<Event> event_;
};

}

#endif /* defined(__kawaii__process_event_emit__) */
