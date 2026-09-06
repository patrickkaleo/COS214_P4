#include "TGIterator.h"

TGIterator::TGIterator(const std::vector<Task *> &children)
{
	this->children = children;
	this->current = this->children.begin();
}

Iterator *TGIterator::operator++()
{
	if (current != children.end())
		++current;
	return this;
}

Iterator *TGIterator::operator--()
{
	if (current != children.begin())
		--current;
	return this;
}

Task &TGIterator::operator*()
{
	return **current;
}

bool TGIterator::operator==(const Iterator &other) const
{
	if (&other == this)
		return true;
	const TGIterator *rhs = dynamic_cast<const TGIterator *>(&other);
	if (rhs == nullptr)
		return false;
	if (children != rhs->children)
		return false;
	return (current - children.begin()) == (rhs->current - rhs->children.begin());
}

Iterator* TGIterator::begin() {
    current = children.begin();
    return this;
}

Iterator* TGIterator::end() {
    current = children.end();
    return this;
}