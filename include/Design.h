#ifndef DESIGN_H
#define DESIGN_H
#include "TaskState.h"
class Design : public TaskState {
public:
    std::string state() const override;
    void updateState() override;
};
#endif
