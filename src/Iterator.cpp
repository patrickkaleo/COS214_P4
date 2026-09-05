#include "Iterator.h"

Iterator::Iterator()
{
	current = children.begin();
}

bool Iterator::isStart() 
{
	return this->current==this->children.begin();
}

bool Iterator::isEnd() 
{
	return this->current==this->children.end();
}

Iterator::Iterator(const Iterator &other) : children(other.children)
{
	current = children.begin() + (other.current - other.children.begin());
}
