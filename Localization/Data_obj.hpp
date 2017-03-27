#ifndef DATA_OBJ_HPP
#define DATA_OBJ_HPP
#include<memory>
#include<opencv2/opencv.hpp> 
#include<string>
class Data_obj
{
	public:
		std::shared_ptr<int> ping_data;
		std::shared_ptr<cv::Mat> image_data; 
		Data_obj():ping_data(nullptr),image_data(nullptr){};
};

#endif
