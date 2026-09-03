#include "BFSIterator.h"
Iterator* BFSIterator::operator++() { return this; }
Iterator* BFSIterator::operator--() { return this; }
Task& BFSIterator::operator*() { return *current; }
bool BFSIterator::operator==(const Iterator& other) const { return this->current == &(*const_cast<Iterator&>(other)); }
