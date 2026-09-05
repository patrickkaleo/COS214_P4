#ifndef ITERATOR_H
#define ITERATOR_H
#include <vector>

#include "Task.h"
/**
 * @class Iterate: Defines the interface for traversing the TakGroup without exposing the childrens vector
 * @brief Participation: Iterator in Iterator DP.
 */
class Iterator
{

public:
	Iterator() {}
	virtual ~Iterator() {};
	
	/**
	 * @brief iterate to the next item
	 * @return Iterator* iterator containing the details of the current item accessible to the client
	 */
	virtual Iterator *operator++() = 0;
	
	/**
	 * @brief Get Task from iterator object
	 * @return Task& : memory address of the current Task in the iterator 
	 */
	virtual Task &operator*() = 0;
	
	/**
	 * @brief Check if 2 iterators are equal
	 * - do they have the same pointer?
	 * - do they have the same current? i.e pointing to the same object
	 */
	virtual bool operator==(const Iterator &other) const = 0;
	
	/**
	 * @brief return iterator pointing to the first object in the children's vector list
	 * @return Iterator*
	 */
	bool isStart();
	
	/**
	 * @brief return iterator pointing to the last element in the childrens array
	 * @return Iterator*
	 */
	bool isEnd();

protected:
	Iterator(const Iterator &other);
	std::vector<Task *> children;
	std::vector<Task *>::iterator current;
};
#endif
