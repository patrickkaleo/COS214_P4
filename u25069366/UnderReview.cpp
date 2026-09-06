#include "UnderReview.h"
#include <iostream>
#include "Task.h"
#include "TaskState.h"
using namespace std;

UnderReview::UnderReview(Task* context) : TaskState(context){}
        
string UnderReview::state()const{
    return "Under Review";
}


void UnderReview::updateState(TaskState* requested, bool testPassed){
    if(requested->state() == "Deployed" && testPassed){
        context->setState(requested);
    }
    else if(requested->state() == "Implementation"){
        context->setState(requested);
    }
    else{
        cout << "Invalid Request";
        delete requested; // rejected: nobody adopted it, so we must free it
    }
}
