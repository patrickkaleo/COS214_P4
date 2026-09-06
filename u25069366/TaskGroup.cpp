#include "TaskGroup.h"
#include "TGIterator.h"
#include "StateIterator.h"

TaskGroup::TaskGroup(std::string description) : Task(description){}

TaskGroup::~TaskGroup()
{
	for (auto child : children)
		delete child;
}

void TaskGroup::logState() const
{
	Task::logState();
	for (auto child : children)
		child->logState();
}

void TaskGroup::updateState(TaskState* newState, bool testPassed) {
    for (auto child : this->children)
        child->updateState(newState, testPassed);
}

void TaskGroup::add(Task *child)
{
	if (child != nullptr)
	{
		for (auto iterate : children)
		{
			if (child == iterate)
				return;
		}
		children.push_back(child);
	}
}

TGIterator *TaskGroup::createTGIterator() { 
	return new TGIterator(this->children); 
}

StateIterator *TaskGroup::createStateIterator(TaskState* state) { 
	return new StateIterator(children, state); 
}

std::vector<Task*> TaskGroup::getChildren() const
{
	return children;
}

Iterator* TaskGroup::begin()
{
	return createTGIterator();
}

Iterator* TaskGroup::end()
{
	TGIterator* it = new TGIterator(this->children);
	return it->end();
}
