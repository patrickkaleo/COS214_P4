#ifndef UNDER_REVIEW_H
#define UNDER_REVIEW_H
#include "TaskState.h"
class Task;

class UnderReview : public TaskState{
    public:
        UnderReview(Task* context);
        
        std::string state()const;
        void updateState(TaskState* requested);
};
#endif
