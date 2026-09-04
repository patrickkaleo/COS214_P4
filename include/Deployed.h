#ifndef DEPLOYED_H
#define DEPLOYED_H
#include "TaskState.h"
#include "Task.h"

class Task;
class Deployed : public TaskState{
    public:
        Deployed(Task* context);

        std::string state()const;
        void updateState(TaskState* requested);
};

#endif
