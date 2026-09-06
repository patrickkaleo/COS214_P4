#include "PriorityDecorator.h"
#include <iostream>
using namespace std;

PriorityDecorator::PriorityDecorator(Task* task, string level) : TaskDecorator(task), priorityLevel(level){}

void PriorityDecorator::logState()const {
    cout << "Priority " << priorityLevel << "\n";
    TaskDecorator::logState();
}