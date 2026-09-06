#include "StateIterator.h"

StateIterator::StateIterator(std::vector<Task *> &children, TaskState *state)
{
	if (this->state)
		this->state = state;
	else
		this->state = new Design(nullptr); // Default state
	this->children = children;
	this->current = this->children.begin();
}

StateIterator::~StateIterator()
{
	if (this->state)
		delete this->state;
	this->state = nullptr;
}

Iterator *StateIterator::operator++()
{
	if (this->state != nullptr)
	{
		while (this->current != this->children.end())
		{
			Task *item = *this->current;
			if (this->state->state() == item->getState()->state())
				break;
			++this->current;
		}
	}
	else
	{
		while (this->current != this->children.end())
		{
			Task *item = *this->current;
			if (item->getState() == nullptr)
				break;
			++this->current;
		}
	}

	return this;
}

Iterator *StateIterator::operator--()
{
	if (this->state != nullptr)
	{
		while (this->current != this->children.begin())
		{
			Task *item = *this->current;
			if (this->state->state() == item->getState()->state())
				return this;
			--this->current;
		}
	}
	else
	{
		while (this->current != this->children.end())
		{
			Task *item = *this->current;
			if (item->getState() == nullptr)
				break;
			++this->current;
		}
	}
	return this;
}

Task &StateIterator::operator*()
{
	return **current;
}

bool StateIterator::operator==(const Iterator &other) const
{
	if (&other == this)
		return true;
	const StateIterator *rhs = dynamic_cast<const StateIterator *>(&other);
	if (rhs == nullptr)
		return false;
	if (children != rhs->children)
		return false;
	return (current - children.begin()) == (rhs->current - rhs->children.begin());
}
