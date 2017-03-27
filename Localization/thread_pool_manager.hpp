#ifndef THREAD_POOL_MANAGER
#define THREAD_POOL_MANAGER 
#include"threadPool.hpp"
#include"Data_obj.hpp"
#include<mutex>
#include<condition_variable>
#include<memory>
#include<thread>
#include"ITask.hpp"
#include"factory.hpp"
class thread_pool_manager
{
	private:
		bool _kill_flag;
		factory fac;
		std::mutex _flag_mutex;
		std::mutex _data_mutex;
		std::condition_variable _cond_var;
		std::shared_ptr<std::thread> main_thread; 
		threadPool _pool;
		bool is_done();
		void kill();
		void start_task(std::shared_ptr<ITask>);
		Data_obj _data;
	public:
		enum task_id{BUEY_TASK,GATE_TASK,PINGER_TASK};
		thread_pool_manager();
		std::vector<std::shared_ptr<ITask>> _tasks;
		~thread_pool_manager();
		void input_data(Data_obj);
		void execute(); 
};
thread_pool_manager::~thread_pool_manager()
{
	std::cout<<"entered destructor\n";
//	std::this_thread::sleep_for(std::chrono::seconds(10));	
	main_thread->join();
}
bool thread_pool_manager::is_done()
{
	std::lock_guard<std::mutex> temp_lock(_data_mutex);
	return _kill_flag;
}
thread_pool_manager::thread_pool_manager():_pool(4)
{

	_tasks.resize(3);
	_tasks[0]=fac.create_update_buey_task();	
	_tasks[1]=fac.create_update_gate_task();
	_tasks[2]=fac.create_update_pinger_task();
		_kill_flag=false;
//	main_thread=std::make_shared<std::thread>(std::thread([&](){execute();}));
}
void thread_pool_manager::execute()
{ 
	while(true)
	{ 
		for(uint i=0; i<_tasks.size(); i++)
		{
			start_task(_tasks[i]);			
		}
	}

}
void thread_pool_manager::start_task(std::shared_ptr<ITask> in_function)
{	
	if(in_function->should_execute()){


		_pool.enqueue_work([&,in_function](){
				in_function->task_function(_data);
				}); 
	}

}
void thread_pool_manager::input_data(Data_obj new_data)
{
	std::lock_guard<std::mutex> temp_lock(_data_mutex);
	_data=new_data;
}
void thread_pool_manager::kill()
{
	std::lock_guard<std::mutex> temp_lock(_flag_mutex);
	_kill_flag=true;
}
#endif
