#include "Deployed.h"
#include <iostream>
#include "Task.h"
#include "TaskState.h"
using namespace std;

Deployed::Deployed(Task* context) : TaskState(context){}

string Deployed::state()const{
    return "Deployed";
}

void updateState(TaskState* requested){
    cout << "This Task is already deployed\n";
}

