#ifndef TASK_GROUP_H
#define TASK_GROUP_H
#include "Task.h"
#include <vector>
class TaskGroup : public Task {
private:
    std::vector<Task*> children;
public:
    TaskGroup(std::string description);
    ~TaskGroup() override;
    void logState() const override;
    void updateState(TaskState* newState) override;
    Iterator* begin() override;
    Iterator* end() override;
    void add(Task* child) override;
    TGIterator* createTGIterator() override;
    BFSIterator* createBFSIterator() override;
};
#endif
