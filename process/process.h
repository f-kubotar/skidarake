#ifndef __kawaii__process_process__
#define __kawaii__process_process__

#include "kawaii/hashed_string.h"
#include "kawaii/types.h"
#include "kawaii/memory_pool.h"
#include "kawaii/process/process_scheduler.h"

#include <memory>

namespace kawaii {
using namespace std;

class Process : public GeneralPoolable,
                public enable_shared_from_this<Process> {
public:
    // typedef enum {
    //     ATTACHED = 0x00000001,
    // } Flags;

    Process()
        : killed_(false),
          paused_(false),
          initialized_(false),
          sleeping_(false) {
    }
    
    virtual ~Process() {}

    const bool killed() const {
        return killed_;
    }

    const bool dead() const {
        return killed_;
    }

    const bool paused() const {
        return paused_;
    }

    const bool initialized() const {
        return initialized_;
    }

    const bool sleeping() const {
        return sleeping_;
    }

    virtual bool Visit(const ii_time delta_time) {
        if (!initialized_) {
            OnEnter();
            initialized_ = true;
        }
        if (!dead()) {
            return Update(delta_time);
        }
        return false;
    }
    
    void Kill() {
        killed_ = true;
        OnExit();
    }

    void Sleep()  { sleeping_ = true; }
    void Wakeup() { sleeping_ = false; }
    void Pause()  { paused_ = true; }
    void Resume() { paused_ = false; }

    void Run() { scheduler().Attach(shared_from_this()); }

    virtual ProcessScheduler& scheduler();
    virtual void OnEnter() {}
    virtual void OnExit() {}
    virtual bool Update(const ii_time delta) = 0;
    
    virtual const HashedString& type() const = 0;
    virtual size_t target_id() { return 0; }

protected:
    bool killed_;
    bool paused_;
    bool sleeping_;
    bool initialized_;

private:
    Process(const Process&);
    Process& operator=(const Process&);

    unsigned int flags;
};

}

#endif /* defined(__kawaii__process_process__) */
