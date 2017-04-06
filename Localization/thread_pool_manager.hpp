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
		std::mutex _data_flag_mutex;
		std::condition_variable _cond_var;
		std::shared_ptr<std::thread> main_thread; 
		std::shared_ptr<threadPool> _pool;
		bool is_done();
		void kill();
		void start_task(std::shared_ptr<ITask>,Data_obj);
		void wait_for_data();
		Data_obj get_data_front();
		bool data_present();
		std::shared_ptr<std::queue<Data_obj>> _data_queue;
		void execute(); 
		std::vector<std::shared_ptr<ITask>> _tasks;
	public:
		enum task_id{BUEY_TASK,GATE_TASK,PINGER_TASK};
		enum task_status{ACTIVE,INACTIVE}; 
		thread_pool_manager();
		~thread_pool_manager();
		void input_data(Data_obj);
		void set_task_status(task_id input_task,task_status input_status);
}; 
void thread_pool_manager::set_task_status(task_id in_task,task_status status)
{
	std::lock_guard<std::mutex> _lock(_data_mutex);
	switch(in_task)
	{
		case BUEY_TASK:
			switch(status)
			{
				case ACTIVE:
					_tasks[BUEY_TASK]->set_status(true);
					break;
				case INACTIVE:
					_tasks[BUEY_TASK]->set_status(false);
					break;
			}
			break;
		case GATE_TASK:
			switch(status)
			{
				case ACTIVE:
					_tasks[GATE_TASK]->set_status(true);
					break;
				case INACTIVE:
					_tasks[GATE_TASK]->set_status(false);
					break;
			}
			break;
		case PINGER_TASK:
			switch(status)
			{
				case ACTIVE:
					_tasks[PINGER_TASK]->set_status(true);
					break;
				case INACTIVE:
					_tasks[PINGER_TASK]->set_status(false);
					break; 
			}
			break; 
	}
}
void thread_pool_manager::wait_for_data()
{
	//std::cout<<"wait_for_data is waitig for mutex\n";
	std::unique_lock<std::mutex> temp_lock(_data_mutex); 
	//std::cout<<"waiting for data has mutex\n";
	while(_data_queue->empty()&&!_kill_flag)
	{
		//std::cout<<"going to sleep...................................\n";
		_cond_var.wait(temp_lock);
	}
	//std::cout<<"woke up!.......\n";
	//std::cout<<"number in queue: "<<_data_queue->size()<<std::endl;
}
thread_pool_manager::~thread_pool_manager()
{
	//std::cout<<"entered destructor\n";
	kill();
	//std::cout<<"going to join...\n";
	main_thread->join();
	//	std::cout<<"joined\n";
	//	_data_queue=nullptr;
	//	std::cout<<"is null now\n";
	//	std::cout<<_data_queue->size()<<std::endl;
	//	_data_queue->push(Data_obj());
	//	std::this_thread::sleep_for(std::chrono::seconds(10));
}
bool thread_pool_manager::is_done()
{
	//std::cout<<"is_open waiting on data_mutex\n";
	std::lock_guard<std::mutex> temp_lock(_flag_mutex);
	//std::cout<<"is_open has data_mutex\n";
	return _kill_flag;
}
thread_pool_manager::thread_pool_manager()
{
	_data_queue=std::make_shared<std::queue<Data_obj>>();
	//std::cout<<"constructor: "<<_data_queue->size()<<std::endl;
	_pool=std::make_shared<threadPool>(4);
	_tasks.resize(3);
	_tasks[0]=fac.create_update_buey_task();	
	_tasks[1]=fac.create_update_gate_task();
	_tasks[2]=fac.create_update_pinger_task();
	_kill_flag=false;
	main_thread=std::make_shared<std::thread>(std::thread([&](){execute();}));
}
bool thread_pool_manager::data_present()
{
	//std::cout<<"data_present waiting on data_mutex\n";
	std::lock_guard<std::mutex> temp_lock(_data_mutex);
	//std::cout<<"data_present owns data_mutex\n"; 
	return !_data_queue->empty();
}
Data_obj thread_pool_manager::get_data_front()
{
	//std::cout<<"data_front waiting on data_mutex\n";
	std::lock_guard<std::mutex> temp(_data_mutex); 
	//std::cout<<"data_front has data_mutex\n"; 
	Data_obj returned=_data_queue->front();
	//std::cout<<"line 102\n";
	_data_queue->pop(); 
	//std::cout<<"line 104\n";
	return returned;
}
void thread_pool_manager::execute()
{ 
	while(!is_done())
	{

		wait_for_data();
		if(_data_queue->empty())
		{ 
			//std::cout<<"queue empty, breaking....\n";
			break;
		}
		//std::cout<<"line 152\n";
		auto temp_data=get_data_front(); 
		//std::cout<<"line 154\n";
		//std::cout<<"task size: "<<_tasks.size()<<std::endl;
		for(uint i=0; i<_tasks.size(); i++)
		{
			//std::cout<<"line 157\n";
			start_task(_tasks[i],temp_data);			
		} 
	}

}
void thread_pool_manager::start_task(std::shared_ptr<ITask> in_function,Data_obj data_in)
{
	//std::cout<<"start_task waiting on _data_mutex\n";
	std::lock_guard<std::mutex> temp(_data_mutex);
	//std::cout<<"start_task has data_mutex\n";
	if(in_function->should_execute()){ 
		_pool->enqueue_work([&,in_function](){
				if(!is_done()) 
				{
				in_function->task_function(data_in);

				}				}); 
	} 
}
void thread_pool_manager::input_data(Data_obj new_data)
{
	//std::cout<<"input_data waiting on data_mutex\n";
	std::lock_guard<std::mutex> temp_lock(_data_mutex);
	//std::cout<<"input_data has data_mutex\n";
	std::lock_guard<std::mutex> temp2_lock(_data_flag_mutex); 
	//std::cout<<"input data has both mutexes.\n";
	_data_queue->push(new_data);
	_cond_var.notify_all(); 
}
void thread_pool_manager::kill()
{
	std::lock_guard<std::mutex> temp_lock(_flag_mutex);
	//std::cout<<"entered kill function\n";
	_kill_flag=true;
	_cond_var.notify_all();
}
#endif
