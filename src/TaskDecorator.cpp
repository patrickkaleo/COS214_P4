#include "TaskDecorator.h"
#include "TGIterator.h"
#include "StateIterator.h" 

TaskDecorator::TaskDecorator(Task* target, std::string decorationText) 
	: Task(target->getDescription()), item(target), deco(decorationText) {}
TaskDecorator::~TaskDecorator() { delete item; }
std::string TaskDecorator::decoration() const { return deco; }
TGIterator* TaskDecorator::createTGIterator() { return item->createTGIterator(); }
StateIterator* TaskDecorator::createStateIterator() { return item->createStateIterator(); }
