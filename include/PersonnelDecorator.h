#ifndef PERSONNEL_DECORATOR_H
#define PERSONNEL_DECORATOR_H
#include "TaskDecorator.h"
class PersonnelDecorator : public TaskDecorator {
public:
    using TaskDecorator::TaskDecorator;
    std::string decoration() const override;
};
#endif
