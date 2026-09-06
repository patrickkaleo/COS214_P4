#include <iostream>
#include <string>

#include "TaskGroup.h"
#include "UnitTask.h"
#include "StateIterator.h"
#include "StateIterator.h"

using namespace std;


int main()
{
	// Iterator Testing:
	Task* tg1= new TaskGroup(nullptr);
	Task*t1=new UnitTask("T01");
	t1->setState(new Design(t1));
	Task*t2=new UnitTask("T02");
	t2->setState(new Design(t2));
	Task*t3=new UnitTask("T03");
	t3->setState(nullptr);
	tg1->add(t1);
	tg1->add(t2);
	tg1->add(t3);
	
	tg1->logState();
	StateIterator* si1= tg1->createStateIterator(nullptr);
	while(!si1->isEnd()) 
	{
		(si1)->operator*().logState();
	}
	
	
	
	
	return 0;
}
