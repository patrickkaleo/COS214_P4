#ifndef BFS_ITERATOR_H
#define BFS_ITERATOR_H
#include "Iterator.h"
class BFSIterator : public Iterator {
public:
    using Iterator::Iterator;
    Iterator* operator++() override;
    Iterator* operator--();
    Task& operator*() override;
    bool operator==(const Iterator& other) const override;
};
#endif
