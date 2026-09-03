#include "TGIterator.h"
Iterator* TGIterator::operator++() { return this; }
Iterator* TGIterator::operator--() { return this; }
Task& TGIterator::operator*() { return *current; }
bool TGIterator::operator==(const Iterator& other) const { return this->current == &(*const_cast<Iterator&>(other)); }
