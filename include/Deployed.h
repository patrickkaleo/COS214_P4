#ifndef DEPLOYED_H
#define DEPLOYED_H
#include "TaskState.h"
class Deployed : public TaskState {
public:
    std::string state() const override;
    void updateState() override;
};
#endif
