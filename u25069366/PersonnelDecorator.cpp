#include "PersonnelDecorator.h"
using namespace std;
#include <iostream>

PersonnelDecorator::PersonnelDecorator(Task* task, string p) : TaskDecorator(task), personnel(p){}

void PersonnelDecorator::logState()const {
    cout << "Personnel: " << personnel << "\n";
    TaskDecorator::logState();
}