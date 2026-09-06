#ifndef TASK_DECORATOR_H
#define TASK_DECORATOR_H
#include "Task.h"

class StateIterator;
class TGIterator;

class TaskDecorator : public Task {
protected:
    Task* wrappedTask;

public:
    TaskDecorator(Task* task);
    virtual ~TaskDecorator() override;

    void logState() const override;
    void updateState(TaskState* newState, bool testPassed) override;
    void setState(TaskState* newState) override;
    void add(Task* child) override;
    std::string getDescription() const override;

    Iterator* begin() override;
    Iterator* end() override;
    TGIterator* createTGIterator() override;
    StateIterator* createStateIterator(TaskState* state) override;
};
#endif