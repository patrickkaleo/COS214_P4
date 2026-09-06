#ifndef TASK_DECORATOR_H
#define TASK_DECORATOR_H
#include "Task.h"
class TaskDecorator : public Task {
protected:
    Task* wrappedTask;

public:
    TaskDecorator(Task* task);
    virtual ~TaskDecorator();

    void logState() const override;
    void updateState(TaskState* newState) override;
    void setState(TaskState* newState) override;
    void add(Task* child) override;
    std::string getDescription() const override;

    Iterator* begin() override;
    Iterator* end() override;
    TGIterator* createTGIterator() override;
    BFSIterator* createBFSIterator() override;
};
#endif
