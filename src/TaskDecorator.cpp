#include "TaskDecorator.h"
TaskDecorator::TaskDecorator(Task* target, std::string decorationText) 
    : Task(target->getDescription()), item(target), deco(decorationText) {}
TaskDecorator::~TaskDecorator() { delete item; }
std::string TaskDecorator::decoration() const { return deco; }
Iterator* TaskDecorator::begin() { return item->begin(); }
Iterator* TaskDecorator::end() { return item->end(); }
TGIterator* TaskDecorator::createTGIterator() { return item->createTGIterator(); }
BFSIterator* TaskDecorator::createBFSIterator() { return item->createBFSIterator(); }
