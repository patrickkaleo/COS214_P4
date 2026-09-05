#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

// files 
#include "TaskState.h"
#include "Iterator.h"
#include "TGIterator.h"
#include "StateIterator.h"

/**
 * @class Task: Component abstract for composite and decorator class
 */
class Task
{
public:
	Task();
	virtual ~Task();

	/**
	 * @brief Print the status of the component
	 */
	virtual void logState() const;
	
	/**
	 * @brief return the state of the component
	 */
	TaskState* getState();

	/**
	 * @brief update the state to  new state
	 * @param newState new state
	 * @return void
	 */
	void setState(TaskState *newState);

	/**
	 * @brief add child to children (applicable TaskGroup)
	 * @param child
	 * @return void
	 */
	virtual void add(Task *child) {};

	/**
	 * @brief create new TGIterator for normal traversals
	 * @return TGIterator*
	 */
	virtual TGIterator *createTGIterator() { return nullptr; }

	/**
	 * @brief create new StateIterator for normal traversals
	 * @return StateIterator*
	 */
	virtual StateIterator *createStateIterator(TaskState* state) { return nullptr; }

	/**
	 * @brief return the children for the given Task, empty if it is simply a leaf/concrete component
	 * @return std::vector<Task*>
	 */
	virtual std::vector<Task *> getChildren() const { return {}; };

	std::string getDescription() const;

protected:
	std::string description;
	TaskState *state;
};

#endif
