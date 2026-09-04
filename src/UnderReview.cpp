#include "UnderReview.h"
#include <iostream>
#include "Task.h"
#include "TaskState.h"
using namespace std;

UnderReview::UnderReview(Task* context) : TaskState(context){}
        
string UnderReview::state()const{
    return "Under Review";
}


void UnderReview::updateState(TaskState* requested){
    if(requested->state() == "Deployed"){
        context->setState(requested);
        delete this;
    }
    if(requested->state() == "Implemenation"){
        context->setState(requested);
        delete this;
    }
    else{
        cout << "Invalid Request";
    }
}
