#include "Task.h"
#include "TGIterator.h"
#include "StateIterator.h"
#include <stdexcept>

Task::Task(std::string desc) : description(desc), state(nullptr)
{
	state = new Design(this);
}

void Task::updateState(TaskState *newState, bool testPassed)
{
	TaskState *old = state;
	old->updateState(newState, testPassed);
	if (state != old)
		delete old;
}

void Task::add(Task *child)
{
	//do nothing;
}

Task::~Task() { delete state; }

void Task::setState(TaskState *newState)
{
	 this->state=newState;
}

void Task::logState() const
{
	std::cout << "Task: " << description << " | Status: " << (this->state ? state->state() : "null") << "\n";
}

TaskState *Task::getState() const
{
	return state;
}

std::string Task::getDescription() const { return this->description; }