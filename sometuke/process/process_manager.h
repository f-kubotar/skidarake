#ifndef __sometuke__process_process_manager__
#define __sometuke__process_process_manager__

#include "sometuke/types.h"
#include "sometuke/scheduler.h"

#include <memory>
#include <list>
#include <unordered_map>

namespace sometuke {
using namespace std;

class Process;

typedef list<shared_ptr<Process> > ProcessList;

class ProcessManager {
public:
    shared_ptr<Process> Attach(const shared_ptr<Process>& process);
    void Dettach(const shared_ptr<Process>& process);
    bool Update(const s2_time delta_time);

private:
    ProcessList process_list_;
};

}

#endif /* defined(__sometuke__process_process_manager__) */
