#ifndef TASK_DECORATOR_H
#define TASK_DECORATOR_H
#include "Task.h"
class TaskDecorator : public Task {
protected:
    Task* item;
    std::string deco;
public:
    TaskDecorator(Task* target, std::string decorationText);
    virtual ~TaskDecorator() override;
    virtual std::string decoration() const;
    Iterator* begin() override;
    Iterator* end() override;
    TGIterator* createTGIterator() override;
    BFSIterator* createBFSIterator() override;
};
#endif
