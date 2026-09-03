#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H
#include "TaskState.h"
class Implementation : public TaskState {
public:
    std::string state() const override;
    void updateState() override;
};
#endif
