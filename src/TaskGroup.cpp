#include "TaskGroup.h"
#include "TGIterator.h"
#include "BFSIterator.h"
TaskGroup::TaskGroup(std::string description) : Task(description) {}
TaskGroup::~TaskGroup() { for (auto child : children) delete child; }
void TaskGroup::logState() const {
    Task::logState();
    for (auto child : children) child->logState();
}
void TaskGroup::updateState(TaskState* newState) { Task::updateState(newState); }
void TaskGroup::add(Task* child) { children.push_back(child); }
Iterator* TaskGroup::begin() { return createTGIterator(); }
Iterator* TaskGroup::end() { return nullptr; } 
TGIterator* TaskGroup::createTGIterator() { return new TGIterator(this, children); }
BFSIterator* TaskGroup::createBFSIterator() { return new BFSIterator(this, children); }
