#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H
#include "TaskState.h"
class Task;

class Implementation : public TaskState{
    public:
        Implementation(Task* context);

        std::string state()const;
        void updateState(TaskState* requested);
};
#endif
