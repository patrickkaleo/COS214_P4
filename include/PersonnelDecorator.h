#ifndef PERSONNEL_DECORATOR_H
#define PERSONNEL_DECORATOR_H
#include "TaskDecorator.h"
class PersonnelDecorator : public TaskDecorator {
    private:
        std::string personnel;

    public:
        PersonnelDecorator(Task* task, std::string level);
        void logState()const override;
};
#endif
