#ifndef DATA_OBJ_HPP
#define DATA_OBJ_HPP
#include<memory>
#include<opencv2/opencv.hpp> 
//#include<string>
class Data_obj
{
	public:
		
		int ping_data;
		cv::Mat image_data; 
		Data_obj(){};
		
		/*
		int ping_data;
		Data_obj():ping_data(0){};
		*/
};

#endif
