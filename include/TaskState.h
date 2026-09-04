#ifndef TASKSTATE_H
#define TASKSTATE_H
#include <string>
#include <iostream>

class Task;

class TaskState{
    protected:
        Task* context;

    public:
        TaskState(Task* context);
        virtual ~TaskState();

        virtual std::string state()const = 0;
        virtual void updateState(TaskState* requested) = 0;
};

#endif //TASKSTATE_H