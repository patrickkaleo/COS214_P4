#ifndef TASK_STATE_H
#define TASK_STATE_H
#include <string>
class TaskState {
public:
    virtual ~TaskState() = default;
    virtual std::string state() const = 0;
    virtual void updateState() = 0;
};
#endif
