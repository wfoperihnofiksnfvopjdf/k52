/*
 * ThreadWorkerPoolTemplated.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOLTEMPLATED_H_
#define THREADWORKERPOOLTEMPLATED_H_

#ifdef BUILD_WITH_BOOST_THREAD

#include "worker.h"

#include <common/disallow_copy_and_assign.h>

namespace k52
{
namespace parallel
{
namespace thread
{

template <class Task>
class ThreadWorkerPoolTemplated
{
public:
	ThreadWorkerPoolTemplated();

	ThreadWorkerPoolTemplated(int numberOfWorkers);

	~ThreadWorkerPoolTemplated();

	void doTasks(std::queue<Task> tasks);

private:
	void initialize();

	int _numberOfWorkers;
	Worker<Task>* _workers;
	ThreadSafeQueue<Task> _tasksToDo;
	ThreadSafeQueue<Task> _doneTasks;

	DISALLOW_COPY_AND_ASSIGN(ThreadWorkerPoolTemplated);
};

template <class Task>
void ThreadWorkerPoolTemplated<Task>::initialize()
{
	if(_numberOfWorkers <= 0)
	{
		throw std::invalid_argument("numberOfWorkers must be positive");
	}

	_workers = new Worker<Task> [_numberOfWorkers];

	//TODO do not start immediatelly?
	for(int i=0; i<_numberOfWorkers; i++)
	{
		_workers[i].Start(&_tasksToDo, &_doneTasks);
	}
}

template <class Task>
ThreadWorkerPoolTemplated<Task>::ThreadWorkerPoolTemplated()
{
	_numberOfWorkers = boost::thread::hardware_concurrency();
	initialize();
}

template <class Task>
ThreadWorkerPoolTemplated<Task>::ThreadWorkerPoolTemplated(int numberOfWorkers)
{
	_numberOfWorkers = numberOfWorkers;
	initialize();
}

template <class Task>
ThreadWorkerPoolTemplated<Task>::~ThreadWorkerPoolTemplated()
{
	for(int i=0; i<_numberOfWorkers; i++)
	{
		_workers[i].Stop();
	}

	//Wait for correct finalization of all threads
	for(int i=0; i<_numberOfWorkers; i++)
	{
		_workers[i].Join();
	}

	delete [] _workers;
}

template <class Task>
void ThreadWorkerPoolTemplated<Task>::doTasks(std::queue<Task> tasks)
{
	int n = tasks.size();

	while(!tasks.empty())
	{
		_tasksToDo.Push(tasks.front());
		tasks.pop();
	}

	for(int i=0; i<n; i++)
	{
		Task doneTask;
		_doneTasks.WaitAndPop(doneTask);
	}
}

} /* namespace thread */
} /* namespace parallel */
} /* namespace k52 */

#endif

#endif /* THREADWORKERPOOLTEMPLATED_H_ */
