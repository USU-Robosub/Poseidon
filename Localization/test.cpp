//#include"factory.hpp"
#include<cstdlib>
#include"data_obj.hpp"
#include"task.hpp"
#include"data_obj.hpp"
#include<memory>
void test_function(data_obj test_obj)
{
	std::cout<<test_obj.ping_data<<std::endl;
	std::cout<<test_obj.image_data<<std::endl;
	std::cout<<test_obj.should_execute<<std::endl;
}
int main()
{
	
//	factory test_fac;
//	test_fac.ready();
	data_obj test_obj;	
	task test(test_function);
	std::shared_ptr<task> ptr=std::make_shared<task>(test); 
	ptr->task_function(test_obj);
//	test.task_function(test_obj);
	return EXIT_SUCCESS;	
}
