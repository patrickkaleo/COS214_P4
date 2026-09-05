#ifndef PERSONNELDECORATOR_H
#define PERSONNELDECORATOR_H
#include "TaskDecorator.h"
class PersonnelDecorator : public TaskDecorator {
public:
    using TaskDecorator::TaskDecorator;
    std::string decoration() const override;
};
#endif
