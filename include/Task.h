#ifndef TASK_H
#define TASK_H
#include <string>
class TaskState;
class Iterator;
class TGIterator;
class BFSIterator;
class Task {
protected:
    std::string description;
    TaskState* state;
public:
    Task(std::string desc);
    virtual ~Task();
    virtual void logState() const;
    virtual void updateState(TaskState* newState);
    virtual Iterator* begin() = 0;
    virtual Iterator* end() = 0;
    virtual void add(Task* child);
    virtual TGIterator* createTGIterator() = 0;
    virtual BFSIterator* createBFSIterator() = 0;
    std::string getDescription() const;
};
#endif
