/*
 * ThreadWorkerPoolTemplated.h
 *
 *  Created on: Mar 3, 2013
 *      Author: feanor
 */

#ifndef THREADWORKERPOOLTEMPLATED_H_
#define THREADWORKERPOOLTEMPLATED_H_

#include "Worker.h"

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
				ThreadWorkerPoolTemplated(int numberOfWorkers);

				~ThreadWorkerPoolTemplated();

				void doTasks(std::queue<Task> tasks);

			private:

				ThreadWorkerPoolTemplated(const ThreadWorkerPoolTemplated& a);
				ThreadWorkerPoolTemplated& operator = (const ThreadWorkerPoolTemplated& a);

				int _numberOfWorkers;
				Worker<Task>* _workers;
				ThreadSafeQueue<Task> _tasksToDo;
				ThreadSafeQueue<Task> _doneTasks;
			};

			template <class Task>
			ThreadWorkerPoolTemplated<Task>::ThreadWorkerPoolTemplated(int numberOfWorkers)
			{
				if(numberOfWorkers <= 0)
				{
					throw std::invalid_argument("numberOfWorkers must be positive");
				}
				_numberOfWorkers = numberOfWorkers;
				_workers = new Worker<Task> [_numberOfWorkers];

				//TODO do not start immediatelly?
				for(int i=0; i<_numberOfWorkers; i++)
				{
					_workers[i].start(&_tasksToDo, &_doneTasks);
				}
			}

			template <class Task>
			ThreadWorkerPoolTemplated<Task>::~ThreadWorkerPoolTemplated()
			{
				for(int i=0; i<_numberOfWorkers; i++)
				{
					_workers[i].stop();
				}

				//Wait for correct finalization of all threads
				for(int i=0; i<_numberOfWorkers; i++)
				{
					_workers[i].join();
				}

				delete [] _workers;
			}

			template <class Task>
			void ThreadWorkerPoolTemplated<Task>::doTasks(std::queue<Task> tasks)
			{
				int n = tasks.size();

				while(!tasks.empty())
				{
					_tasksToDo.push(tasks.front());
					tasks.pop();
				}

				for(int i=0; i<n; i++)
				{
					Task doneTask;
					_doneTasks.waitAndPop(doneTask);
				}
			}
		}
	}
}
#endif /* THREADWORKERPOOLTEMPLATED_H_ */