#ifndef __kawaii__ios_touch_dispatcher__
#define __kawaii__ios_touch_dispatcher__

#include "kawaii/application.h"
#include "kawaii/memory_pool.h"

#include <unordered_set>
#include <vector>
#include <map>
#include <memory>

namespace kawaii {
using namespace std;

class Node;

typedef unsigned long TouchId;

typedef enum {
    kTouchBegan,
    kTouchMoved,
    kTouchEnded,
    kTouchCancelled,
} TouchPhase;

struct Touch : public GeneralPoolable {
    static const EventType TYPE;

    Touch(TouchId touch_id, TouchPhase _phase, const vec2& loc, const vec2& prev, size_t cnt)
        : id(touch_id),
          phase(_phase),
          location(loc),
          prev_location(prev),
          tap_count(cnt),
          timestamp(std::time(NULL)) {
    }

    TouchId id;
    TouchPhase phase;
    vec2 location;
    vec2 prev_location;
    size_t tap_count;
    time_t timestamp;
};

typedef vector<shared_ptr<Touch> > TouchSet;
    
class TargetedTouchListener {
public:
    virtual ~TargetedTouchListener() {}

    bool TouchStart(shared_ptr<Touch> touch) {
        bool claimed = TouchBegan(touch);
        if (claimed) {
            claimed_touch_ids_.insert(touch->id);
        }
        return claimed;
    }

    void TouchNext(shared_ptr<Touch> touch, TouchPhase phase) {
        unordered_set<TouchId>::iterator iter = claimed_touch_ids_.find(touch->id);
        if (iter != claimed_touch_ids_.end()) {
            switch (phase) {
            case kTouchMoved:
                TouchMoved(touch);
                break;
            case kTouchEnded:
                TouchEnded(touch);
                claimed_touch_ids_.erase(iter);
                break;
            case kTouchCancelled:
                TouchCancelled(touch);
                claimed_touch_ids_.erase(iter);
                break;
            default:
                break;
            }
        }
    }

    virtual bool listening() const = 0;
    virtual bool shallows_touches() const = 0;

    virtual bool TouchBegan(shared_ptr<Touch> touch) = 0;
    virtual void TouchMoved(shared_ptr<Touch> touch) = 0;
    virtual void TouchEnded(shared_ptr<Touch> touch) = 0;
    virtual void TouchCancelled(shared_ptr<Touch> touch) = 0;

private:
    unordered_set<TouchId> claimed_touch_ids_;
};

class StandardTouchListener {
public:
    virtual ~StandardTouchListener() {}

    virtual bool listening() const = 0;
    virtual void TouchesBegan(TouchSet touches) = 0;
    virtual void TouchesMoved(TouchSet touches) = 0;
    virtual void TouchesEnded(TouchSet touches) = 0;
    virtual void TouchesCancelled(TouchSet touches) = 0;
};
    
typedef multimap<int, shared_ptr<StandardTouchListener> > StandardTouchListenerTable;
typedef multimap<int, shared_ptr<TargetedTouchListener> > TargetedTouchListenerTable;

class TouchDispatcher {
public:    
    static TouchDispatcher& Instance() {
        static unique_ptr<TouchDispatcher> __instance;
        if (!__instance) {
            __instance.reset(new TouchDispatcher);
        }
        return *__instance;
    }

    TouchDispatcher() : enabled_(true) {}

    bool enabled() { return enabled_; }
    void Enable()  { enabled_ = true; }
    void Disable() { enabled_ = false; }

    void AddStandardListener(shared_ptr<StandardTouchListener> listener, int priority);
    void AddTargetedListener(shared_ptr<TargetedTouchListener> listener, int priority);

    void RemoveAllListeners() {
        standard_listeners_.clear();
        targeted_listeners_.clear();
    }
    void RemoveListener(shared_ptr<StandardTouchListener> listener);
    void RemoveListener(shared_ptr<TargetedTouchListener> listener);

    void Trigger(TouchPhase phase, TouchSet touches);

    // vec2 ConvertToGL(const vec2 touch_location) {
    //     vec2 win_size = Application::Instance().size_in_points();
    //     return vec2(touch_location.x, win_size.y - touch_location.y);
    // }
    vec2 ConvertToGL(const vec2 touch_location);

private:
    bool enabled_;
    TargetedTouchListenerTable targeted_listeners_;
    StandardTouchListenerTable standard_listeners_;
};

}

#endif /* defined(__kawaii__ios_touch_dispatcher__) */