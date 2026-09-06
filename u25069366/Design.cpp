#include "Task.h"
#include "Design.h"
#include "TaskState.h"
using namespace std;

class Task;

Design::Design(Task* context) : TaskState(context){}

string Design::state()const{
    return "Design";
}

void Design::updateState(TaskState *requested, bool testPassed){
    if(requested->state() == "Implementation" && testPassed){
        context->setState(requested);
    }
    else{
        cout << "Invalid Request";
        delete requested; // rejected: nobody adopted it, so we must free it
    }
}
