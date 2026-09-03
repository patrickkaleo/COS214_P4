#ifndef ITERATOR_H
#define ITERATOR_H
#include <vector>
class Task;
class Iterator {
protected:
    Task* current;
    std::vector<Task*> children;
public:
    Iterator(Task* start, const std::vector<Task*>& list);
    virtual ~Iterator() = default;
    virtual Iterator* operator++() = 0;
    virtual Task& operator*() = 0;
    virtual bool operator==(const Iterator& other) const = 0;
};
#endif
