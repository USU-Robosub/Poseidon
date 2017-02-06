#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP
#include<queue>
#include<vector>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<functional>
#include<iostream>
#include<utility>
class thread_pool
{
	public:
		thread_pool(int threadNum=-1);
		~thread_pool();
		void enqueue_work(std::function<void()>);
		bool queue_empty(); 
	private:
		/*==============================
		            variables 
		  ==============================*/
		int num_of_threads;
		bool terminate;
		std::vector<std::thread> worker_threads;
		std::queue<std::function<void()>> work_queue;
		std::mutex queue_mutex;
		std::condition_variable cond_var;
		std::vector<bool> thread_done;
		/*==============================
		            functions 
		  ==============================*/
		void thread_worker(int);
		std::function<void()> dequeue();
}; 

thread_pool::thread_pool(int threadNum)
{
	num_of_threads=(threadNum<2?std::thread::hardware_concurrency():threadNum);
	if(num_of_threads==0) throw "error initializing threads.\n";
	terminate=false;
	worker_threads.reserve(num_of_threads);
	for(int i=0; i<num_of_threads; i++)
	{
		worker_threads.push_back(std::thread([&](){ thread_worker(i);}));
		std::cout<<"started thread number: "<<i<<std::endl;
		thread_done.push_back(false);
	} 
}
void thread_pool::thread_worker(int number)
{
	while(!terminate)
	{ 
		while(!queue_empty())
		{
			std::unique_lock<std::mutex> queue_lock(queue_mutex);
			if(terminate&&queue_empty()) break; 
			cond_var.wait(queue_lock,[&](){return !queue_empty();});
			if(terminate&&queue_empty()) break;
			std::function<void()> task=dequeue();		
			queue_lock.unlock();
			task();
		}
		if(terminate&&queue_empty()) break; 

	}
	thread_done[number]=true;
}
std::function<void()> thread_pool::dequeue()
{
	std::function<void()> returned;
	returned=work_queue.front();
	work_queue.pop();
	return returned; 
}
void thread_pool::enqueue_work(std::function<void()> inputFunction)
{
	std::unique_lock<std::mutex> queueLock(queue_mutex);
	work_queue.push(inputFunction);
	queueLock.unlock();
	cond_var.notify_one();

}
thread_pool::~thread_pool()
{
	while(!queue_empty()){ }//wait for all child processes to complete
	std::unique_lock<std::mutex> theLock(queue_mutex);
	terminate=true;
	theLock.unlock();
	cond_var.notify_all(); 

	for(int i=0;i<num_of_threads; i++)
	{
		worker_threads[i].join(); 
	}
}

bool thread_pool::queue_empty()
{
	return work_queue.empty();
}

#endif
