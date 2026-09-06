#include "Deployed.h"
#include <iostream>
#include "Task.h"
#include "TaskState.h"
using namespace std;

Deployed::Deployed(Task* context) : TaskState(context){}

string Deployed::state()const{
    return "Deployed";
}

void Deployed::updateState(TaskState* requested, bool testPassed){
    cout << "This Task is already deployed\n";
    delete requested; // rejected: nobody adopted it, so we must free it
}

