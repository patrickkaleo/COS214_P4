#include "TaskDecorator.h"

TaskDecorator::TaskDecorator(Task* task) : Task(task->getDescription()), wrappedTask(task) {}

TaskDecorator::~TaskDecorator() {
    delete wrappedTask;
}

void TaskDecorator::logState() const {
    wrappedTask->logState();
}

void TaskDecorator::updateState(TaskState* newState, bool testPassed) {
    wrappedTask->updateState(newState, testPassed);
}

void TaskDecorator::setState(TaskState* newState) {
    wrappedTask->setState(newState);
}

void TaskDecorator::add(Task* child) {
    wrappedTask->add(child);
}

std::string TaskDecorator::getDescription() const {
    return wrappedTask->getDescription();
}

Iterator* TaskDecorator::begin() { return wrappedTask->begin(); }
Iterator* TaskDecorator::end() { return wrappedTask->end(); }
TGIterator* TaskDecorator::createTGIterator() { return wrappedTask->createTGIterator(); }
StateIterator* TaskDecorator::createStateIterator(TaskState* state) { return wrappedTask->createStateIterator(state); }