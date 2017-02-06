#include"threadPool.hpp"
#include<cstdlib>
void time_waster(int repNumber)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout<<"job: "<<repNumber<<std::endl;
	return;
}
int main()
{


	thread_pool pool;
	for(int i=0; i<50; i++)
	{
		std::function<void()> temp=std::bind(time_waster,i);
		pool.enqueue_work(temp);
	}
	for(int i=0; i<50; i++)
	{
		std::function<void()> temp=std::bind(time_waster,i*2);
		pool.enqueue_work(temp);
	}
	while(!pool.queue_empty())
	{

	}
	std::cout<<"finished loading pool.\n";
       	

	return EXIT_SUCCESS;
}

