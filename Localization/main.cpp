//#include"factory.hpp"
#include"factory.hpp"
#include"Data_obj.hpp"
#include<cstdlib>
#include<opencv2/opencv.hpp>
#include"thread_pool_manager.hpp"
#include"threadPool.hpp"
#include<memory>
#include<functional>
struct thingy
{
	void test()
	{
		std::cout<<"this is a test.\n";
//		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
};

int main()
{
	Data_obj test_object;
	for(int i=0; i<200; i++)
	{
		threadPool p(6); 
		thread_pool_manager test_manager;
		//	place_holder thing;
		//	thing.task_function(test_obj);
		//	test_thing.test_function();
		//	std::cout<<test_obj.image_data<<std::endl;
		//	t_function->task_function(test_obj);
		p.enqueue_work([&](){test_manager._tasks[thread_pool_manager::PINGER_TASK]->task_function(test_object);});
		p.enqueue_work([&](){test_manager._tasks[thread_pool_manager::GATE_TASK]->task_function(test_object);});
		p.enqueue_work([&](){test_manager._tasks[thread_pool_manager::BUEY_TASK]->task_function(test_object);});

	}	 
	//		std::shared_ptr<thingy> o=std::make_shared<thingy>(); 
	//		p.enqueue_work([&](){o->test(); });


	//	std::this_thread::sleep_for(std::chrono::seconds(5));
	return EXIT_SUCCESS;
}
