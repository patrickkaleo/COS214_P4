#ifndef TASK_DECORATOR_H
#define TASK_DECORATOR_H
#include "Task.h"

class StateIterator;
class TGIterator; 
class TaskDecorator : public Task {
protected:
	Task* item;
	std::string deco;
public:
	TaskDecorator(Task* target, std::string decorationText);
	virtual ~TaskDecorator() override;
	virtual std::string decoration() const;
	TGIterator* createTGIterator() override;
	StateIterator* createStateIterator(TaskState*) override;
};
#endif
