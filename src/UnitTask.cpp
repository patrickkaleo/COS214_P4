#include "UnitTask.h"
UnitTask::UnitTask(std::string description) : Task(description) {}
Iterator* UnitTask::begin() { return nullptr; }
Iterator* UnitTask::end() { return nullptr; }
TGIterator* UnitTask::createTGIterator() { return nullptr; }
BFSIterator* UnitTask::createBFSIterator() { return nullptr; }
