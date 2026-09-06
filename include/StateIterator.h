#ifndef StateIterator_H
#define StateIterator_H

#include "Iterator.h"
#include "TaskState.h"
#include "Design.h"

/**
 * @class StateIterator: Concrete iterator trversing the children and pring the children of the a child
 * - iterates through items who children arrays are empty {}, ignoring all children whos children arent empty
 */
class StateIterator : public Iterator
{

public:
	StateIterator(std::vector<Task *> &children, TaskState* state);
	Iterator *operator++();
	Iterator *operator--();
	Task &operator*();
	bool operator==(const Iterator &other) const;

protected:
	TaskState *state;
};

#endif
