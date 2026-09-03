#ifndef TG_ITERATOR_H
#define TG_ITERATOR_H
#include "Iterator.h"
class TGIterator : public Iterator {
public:
    using Iterator::Iterator;
    Iterator* operator++() override;
    Iterator* operator--();
    Task& operator*() override;
    bool operator==(const Iterator& other) const override;
};
#endif
