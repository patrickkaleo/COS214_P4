#include "UnitTask.h"
#include "TGIterator.h"
#include "StateIterator.h"
using namespace std;

UnitTask::UnitTask(string description) : Task(description){}

// A UnitTask is a leaf: it has no children, so its iterators always
// represent an empty range. begin() == end() immediately, so any loop
// over a leaf's "children" correctly does zero iterations.

TGIterator* UnitTask::createTGIterator() {
    static std::vector<Task*> empty;
    return new TGIterator(empty);
}

StateIterator* UnitTask::createStateIterator(TaskState* state) {
    static std::vector<Task*> empty;
    return new StateIterator(empty, state);
}

Iterator* UnitTask::begin() {
    return createTGIterator();
}

Iterator* UnitTask::end() {
    TGIterator* it = createTGIterator();
    return it->end();
}
