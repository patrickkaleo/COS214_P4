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
	void updateState(TaskState *newState, bool testPassed);
	Iterator *begin();
	Iterator *end();
	void add(Task *child);
	std::vector<Task*> getChildren() const override;
	TGIterator *createTGIterator();
	StateIterator *createStateIterator(TaskState *state) override;

private:
	std::vector<Task *> children;
};
#endif
