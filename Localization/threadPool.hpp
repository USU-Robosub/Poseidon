#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP
#include<queue>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<functional>
#include<vector> 
#include<iostream>
class threadPool
{
	private:
		int _threadNumber;
		bool _done;
		std::vector<std::thread> work_threads; 
		std::queue<std::function<void()>> _work_queue;
	       	std::mutex _queue_mutex; 
		std::condition_variable cond_var;
		void setTerminate(bool);
		void worker_thread(int thread_id);
		void setThread(int thread_id);
		bool ending_conditions();
		bool should_wake_up();
		bool check_for_joinability();
		void wait_for_work();
		std::function<void()> dequeue();
		

	public:
		threadPool(int input=-1);
		~threadPool();
		void enqueue_work(std::function<void()>); 
		std::string mutex_holder;

};

threadPool::threadPool(int input)
{
	std::cout<<"started threadPool\n";
	_threadNumber=(input<2?std::thread::hardware_concurrency(): input);
	setTerminate(false); 
	std::lock_guard<std::mutex> temp_lock(_queue_mutex); 
	
	for(int i=0; i<_threadNumber; i++)
	{
		setThread(i);
	} 

}
void threadPool::setThread(int thread_id)
{

	work_threads.push_back(std::thread([&](){worker_thread(thread_id); }));

}
void threadPool::setTerminate(bool input)
{
	std::lock_guard<std::mutex> temp_lock(_queue_mutex);
	_done=input;
}
void threadPool::worker_thread(int thread_id)
{
	(void) thread_id;
	while(!ending_conditions())
	{ 
		   auto task=dequeue();
		   if(task)
		   {
			   task();
			   cond_var.notify_all();
		   }  
		   else
		   {
			   wait_for_work();
		   }	
	}
	std::cout<<"thread : "<<thread_id<<" ended "<<std::endl;	
}
threadPool::~threadPool()
{
	setTerminate(true); 
	std::cout<<"set terminate threadPool \n";
	while(!check_for_joinability())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
		std::cout<<"notifying...\n";
		cond_var.notify_all();
	} 
	std::cout<<"line 87\n";
	cond_var.notify_all();
	for(int i=0; i<_threadNumber; i++)
	{
		work_threads[i].join();
	}
	std::cout<<"exit threadPool destructor\n";

}
bool threadPool::check_for_joinability()
{
	bool returned=true;
	std::cout<<"thread number: "<<_threadNumber<<std::endl;
	for(int i=0; i<_threadNumber; i++)
	{
		returned=returned&&work_threads[i].joinable();
		std::cout<<"line 102\n";
	}
	std::cout<<"check joinability: "<<returned<<std::endl;
	return returned;
}
bool threadPool::ending_conditions()
{
	std::lock_guard<std::mutex> temp_queue_lock(_queue_mutex);
	return (_done&&_work_queue.empty());
}
std::function<void()> threadPool::dequeue()
{
	std::lock_guard<std::mutex> temp_lock(_queue_mutex);
	if(_work_queue.empty()) return nullptr;
	else
	{
		auto temp=_work_queue.front();
		_work_queue.pop();
		return temp;

	}
}
void threadPool::wait_for_work()
{
	std::unique_lock<std::mutex> temp_lock(_queue_mutex);
	cond_var.wait(temp_lock,[&](){ return true;/*should_wake_up();*/}); 
}
bool threadPool::should_wake_up() 
{
	return !_work_queue.empty()||_done;
} 
void threadPool::enqueue_work(std::function<void()> input_function)
{
	std::lock_guard<std::mutex> temp_lock(_queue_mutex);
	_work_queue.push(input_function);
	cond_var.notify_one();

}




#endif
