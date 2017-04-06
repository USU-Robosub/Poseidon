#ifndef ITASK_HPP
#define ITASK_HPP
#include"Data_obj.hpp"
#include<string>
class ITask
{
	private:
	public:
		virtual std::string get_thing()=0;
		virtual void task_function(Data_obj)=0;
		virtual bool should_execute()=0;
		virtual void set_status(bool)=0;
};
#endif
