#ifndef FACTORY_HPP
#define FACTORY_HPP
#include"Data_obj.hpp"
#include<memory>
#include"ITask.hpp"
#include<functional>
typedef std::function<void(Data_obj)> f_ptr;
//test class representing the overload task functions
class place_holder_buey : public ITask 
{
	private:
		bool executable;
	public:
		place_holder_buey():executable(true),thing("buey"){}; 
		std::string thing;
		std::string get_thing()
		{
			std::cout<<thing<<std::endl;
			return thing;
		}
		~place_holder_buey(){};
		void task_function(Data_obj d)
		{
			(void)d;
			std::cerr<<"Buey: test function\n";
		}
		bool should_execute()
		{
			return executable;
		}
};
class place_holder_gate : public ITask 
{
	private:
		bool executable;
		Data_obj D_obj;
	public:
		std::string thing;
		std::string get_thing()
		{
			std::cout<<thing<<std::endl;
			return thing;
		}
		place_holder_gate():executable(true),thing("gate"){}; 
		~place_holder_gate(){};
		void task_function(Data_obj d)
		{
			(void) d;
			std::cerr<<"Gate: test function\n";
		}
		bool should_execute()
		{
			return executable;
		}

};
class place_holder_pinger : public ITask 
{
	private:
		bool executable;
	public:
		std::string thing;
		std::string get_thing()
		{
			std::cout<<thing<<std::endl;
			return thing;
		}
		place_holder_pinger():executable(true),thing("pinger"){}; 
		~place_holder_pinger(){};
		void task_function(Data_obj d)
		{
			(void)d;
			std::cerr<<"Pinger: test function\n";
		}
		bool should_execute()
		{
			return executable;
		}

};

//note, place_holder is a substitute task object.  This will be 
//replaced with an actual function later.
class factory
{
	private: 
		int num_of_tasks;
	public:
		//	bool ready();
		//	int get_task_number();
		factory(){};
		~factory(){};
		std::shared_ptr<ITask> create_update_buey_task()
		{
			return std::make_shared<place_holder_buey>();
		}
		std::shared_ptr<ITask> create_update_pinger_task()
		{
			return std::make_shared<place_holder_pinger>();
		}
		std::shared_ptr<ITask> create_update_gate_task()
		{
			return std::make_shared<place_holder_gate>();
		}
};

/*
   int factory::get_task_number()
   {
   return num_of_tasks;
   }

   func_type factory::get_task(function_id input_type)
   {
   func_type returned;
   switch(input_type)
   {
   case UPDATE_BUEY:returned=UPDATE_BUEY_TASK;
   break;
   case UPDATE_PINGER: returned=UPDATE_PINGER_TASK;
   break;
   case UPDATE_GATE: returned=UPDATE_GATE_TASK;
   break; 
   }
   return returned; 
   }
   bool factory::ready()
   {
   bool returned=true;
   if(!UPDATE_BUEY_TASK)
   {
   returned=false;
   std::cerr<<"Update buey task not set.\n";	
   }
   if(!UPDATE_PINGER_TASK)
   {
   returned=false;
   std::cerr<<"Update pinger task not set.\n";
   }
   if(!UPDATE_GATE_TASK)
   {
   returned=false;
   std::cerr<<"Update gate task not set. \n";
   }
   if(returned) std::cerr<<"initialization complete\n";
   return returned;	
   }
   */
#endif
