#ifndef DESIGN_H
#define DESIGN_H
#include "TaskState.h"

class Task;
class Design : public TaskState{
    public:
        Design(Task* context);

        std::string state()const;
        void updateState(TaskState* requested);
};
#endif
