#include "Implementation.h"
#include <iostream>
#include "Task.h"
#include "TaskState.h"
using namespace std;


Implementation::Implementation(Task* context) : TaskState(context){}

string Implementation::state()const{
    return "Implementation";
}

void Implementation::updateState(TaskState* requested, bool testPassed){
    if(requested->state() == "Under Review" && testPassed){
        context->setState(requested);
    }
    else{
        cout << "Invalid Request";
        delete requested; // rejected: nobody adopted it, so we must free it
    }
}