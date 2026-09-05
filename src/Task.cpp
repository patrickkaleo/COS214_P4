#include "Task.h"

Task::Task() : state(nullptr) {}

Task::~Task() { delete state; }

void Task::setState(TaskState *newState)
{
	if (this->state)
	{
		delete this->state;
	}
	state = newState;
}

std::string Task::getDescription() const { return description; }

void Task::logState() const
{
	std::cout << "Task: " << description << " | Status: " << (this->state ? state->state() : "null") << "\n";
}

TaskState* Task::getState(){return this->state;}

std::string Task::getDescription() const { return this->description; }
