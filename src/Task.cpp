#include "Task.h"
#include "TGIterator.h"
#include "StateIterator.h"
#include <stdexcept>

Task::Task(std::string desc) : description(desc), state(nullptr) {
	state = new Design(this);
}

void Task::updateState(TaskState* newState, bool testPassed) {
	state->updateState(newState, testPassed);
}

void Task::add(Task* child) {
	throw std::runtime_error("This task cannot have children added to it.");
}

Task::~Task() { delete state; }

void Task::setState(TaskState *newState)
{
	if (this->state)
	{
		delete this->state;
	}
	state = newState;
}

void Task::logState() const
{
	std::cout << "Task: " << description << " | Status: " << (this->state ? state->state() : "null") << "\n";
}

TaskState* Task::getState() const {
	return state;
}

std::string Task::getDescription() const { return this->description; }