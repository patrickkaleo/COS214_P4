#ifndef PRIORITY_DECORATOR_H
#define PRIORITY_DECORATOR_H
#include "TaskDecorator.h"
class PriorityDecorator : public TaskDecorator {
public:
    using TaskDecorator::TaskDecorator;
    std::string decoration() const override;
};
#endif
