#ifndef TASK_GROUP_H
#define TASK_GROUP_H
#include "Task.h"
#include <vector>
class TaskGroup : public Task
{
public:
	TaskGroup(std::string description);
	~TaskGroup();
	void logState() const;
	void updateState(TaskState *newState);
	Iterator *begin();
	Iterator *end();
	void add(Task *child);
	TGIterator *createTGIterator();
	StateIterator *createStateIterator();

private:
	std::vector<Task *> children;
};
#endif
