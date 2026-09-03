#ifndef UNIT_TASK_H
#define UNIT_TASK_H
#include "Task.h"
class UnitTask : public Task {
public:
    UnitTask(std::string description);
    Iterator* begin() override;
    Iterator* end() override;
    TGIterator* createTGIterator() override;
    BFSIterator* createBFSIterator() override;
};
#endif
