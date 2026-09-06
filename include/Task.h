#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

// files
#include "TaskState.h"
#include "Iterator.h"

//forward declarations
class StateIterator;
class TGIterator;

/**
 * @class Task: Component abstract for composite and decorator class
 */
class Task
{
public:
    Task(std::string desc);
    virtual ~Task();

    virtual void logState() const;
    virtual void updateState(TaskState* newState);
    virtual void setState(TaskState* newState);

    virtual Iterator* begin() = 0;
    virtual Iterator* end() = 0;
    virtual void add(Task* child);

    virtual TGIterator* createTGIterator() = 0;
    virtual StateIterator* createStateIterator(TaskState* state) = 0;

    virtual std::vector<Task*> getChildren() const { return {}; }

    virtual std::string getDescription() const;

protected:
    std::string description;
    TaskState* state;
};

#endif