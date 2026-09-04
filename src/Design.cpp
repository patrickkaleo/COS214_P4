#include "Task.h"
#include "Design.h"
#include "TaskState.h"
using namespace std;

class Task;

Design::Design(Task* context) : TaskState(context){}

string Design::state()const{
    return "Design";
}

void Design::updateState(TaskState *requested){
    if(requested->state() == "Implemenation"){
        context->setState(requested);
        delete this;
    }
    else{
        cout << "Invalid Request";
    }
}
