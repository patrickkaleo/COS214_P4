#ifndef TGITERATOR_H
#define TGITERATOR_H
#include "Iterator.h"

/**
 * @class TGIterator: concrete iterator for traversing the children's vector list in TaskGroup
 */
class TGIterator : public Iterator
{
public:
	TGIterator(const std::vector<Task *> &children);
	Iterator *operator++();
	Iterator *operator--();
	Task &operator*();
	bool operator==(const Iterator &other) const;
	Iterator *begin();
	Iterator *end();
};
#endif
