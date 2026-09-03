#include "Iterator.h"
Iterator::Iterator(Task* start, const std::vector<Task*>& list) : current(start), children(list) {}
