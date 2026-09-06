#ifndef PRIORITY_DECORATOR_H
#define PRIORITY_DECORATOR_H
#include "TaskDecorator.h"
class PriorityDecorator : public TaskDecorator {
    private:
        std::string priorityLevel;

    public:
        PriorityDecorator(Task* task, std::string p);
        void logState()const override;
};
#endif
