#include "Task.h"
#include <iostream>
#include <stdexcept>
#include "Design.h"
Task::Task(std::string desc) : description(desc), state(new Design()) {}
Task::~Task() { delete state; }
void Task::logState() const {
    if (state) std::cout << "Task: " << description << " | Status: " << state->state() << "\n";
}
void Task::updateState(TaskState* newState) {
    delete state;
    state = newState;
}
void Task::add(Task* child) { throw std::runtime_error("Leaf configurations cannot append child components."); }
std::string Task::getDescription() const { return description; }
