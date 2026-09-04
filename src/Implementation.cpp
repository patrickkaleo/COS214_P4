#include "Implementation.h"
#include <iostream>
#include "Task.h"
#include "TaskState.h"
using namespace std;


Implementation::Implementation(Task* context) : TaskState(context){}

string Implementation::state()const{
    return "Implementation";
}

void Implementation::updateState(TaskState* requested){
    if(requested->state() == "UnderReview"){
        context->setState(requested);
        delete this;
    }
    else{
        cout << "Invalid Request;"
    }
}