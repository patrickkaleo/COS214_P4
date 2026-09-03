#ifndef UNDER_REVIEW_H
#define UNDER_REVIEW_H
#include "TaskState.h"
class UnderReview : public TaskState {
public:
    std::string state() const override;
    void updateState() override;
};
#endif
