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
	//	for(int i=0; i<200; i++)
	//	{
	
	thread_pool_manager test_manager; 
	/*
	for(int j=0; j<200; j++)
	{ 
		test_manager.input_data(test_object); 
	}
	*/
	test_object.ping_data=0;
	test_manager.input_data(test_object);
	std::cout<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	test_object.ping_data=1;
	test_manager.set_task_status(thread_pool_manager::BUEY_TASK,thread_pool_manager::INACTIVE);
	test_manager.input_data(test_object);
	std::cout<<"buey task inactive\n";
	std::cout<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));


	test_object.ping_data=2;
	test_manager.set_task_status(thread_pool_manager::BUEY_TASK,thread_pool_manager::ACTIVE);
	test_manager.set_task_status(thread_pool_manager::GATE_TASK,thread_pool_manager::INACTIVE);
	test_manager.input_data(test_object);
	std::cout<<"activated buey, deactivated gate\n";
	std::cout<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));


	test_object.ping_data=3;
	test_manager.set_task_status(thread_pool_manager::GATE_TASK,thread_pool_manager::ACTIVE);
	test_manager.set_task_status(thread_pool_manager::PINGER_TASK,thread_pool_manager::INACTIVE);
	test_manager.input_data(test_object);
	std::cout<<"activated gate, deactivated pinger\n";
	std::cout<<std::endl;
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	std::this_thread::sleep_for(std::chrono::seconds(2));


	test_object.ping_data=4;
	test_manager.set_task_status(thread_pool_manager::PINGER_TASK,thread_pool_manager::ACTIVE);
	test_manager.input_data(test_object);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	//	std::this_thread::sleep_for(std::chrono::seconds(2));
	/*
	   test_manager.input_data(test_object);
	   test_manager.input_data(test_object);
	   test_manager.input_data(test_object);
	   std::this_thread::sleep_for(std::chrono::seconds(1));
	   test_manager.input_data(test_object);
	   test_manager.input_data(test_object);
	   */
	//	place_holder thing;
	//	thing.task_function(test_obj);
	//	test_thing.test_function();
	//	std::cout<<test_obj.image_data<<std::endl;
	//	t_function->task_function(test_obj);
	/*
	   p.enqueue_work([&](){test_manager._tasks[thread_pool_manager::PINGER_TASK]->task_function(test_object);});
	   p.enqueue_work([&](){test_manager._tasks[thread_pool_manager::GATE_TASK]->task_function(test_object);});
	   p.enqueue_work([&](){test_manager._tasks[thread_pool_manager::BUEY_TASK]->task_function(test_object);});
	   */

	//	}	 
	//		std::shared_ptr<thingy> o=std::make_shared<thingy>(); 
	//		p.enqueue_work([&](){o->test(); });


	//	std::this_thread::sleep_for(std::chrono::seconds(5));
	return EXIT_SUCCESS;
}
