#ifndef MATH_FUNCTIONS_HPP
#define MATH_FUNCTIONS_HPP
#include<vector>
#include<cmath>
namespace mathFunctions
{
	float correlation_coefficient(float** image, int x, int y,int left_bound_x,int right_bound_x,int higer_bound,int lesser_bound);
	float compute_distance(float x, float y);
}

float mathFunctions::correlation_coefficient(float** image,int x, int y,int left_bound_x,int right_bound_x,int lesser_bound,int higher_bound)
{
	/*====================================
	 * this function takes a double pointer
	 * or rather a pointer to an array that
	 * represents an image.  the DATA_RANGE
	 * variable indicates how far to each 
	 * side of the given pixel the function 
	 * will search for variance.  The function
	 * outputs the correlation coefficient r
	 * for the data within the square sides 
	 * length DATA_RANGE*2 centered at (x,y) 
	 * ===================================*/
	const int DATA_RANGE=7;
	double sum_xy=0;
	double sum_x=0;
	double sum_y=0;
	double sum_x_squared=0;
	double sum_y_squared=0;
	double result=0;
	int n=DATA_RANGE*DATA_RANGE*4;
	std::vector<float> values(DATA_RANGE*4*DATA_RANGE,0);
	std::vector<float> index_value(DATA_RANGE*4*DATA_RANGE,0);
	int startLocation_x=(x-DATA_RANGE<left_bound_x?left_bound_x:x-DATA_RANGE);
	int startLocation_y=(y-DATA_RANGE<lesser_bound?lesser_bound:y-DATA_RANGE);
	int x_range=(startLocation_x+DATA_RANGE*2>right_bound_x?(right_bound_x-startLocation_x):DATA_RANGE*2);
	int y_range=(startLocation_y+DATA_RANGE*2>higher_bound?(higher_bound-startLocation_y):DATA_RANGE*2);


	for(int i=0; i<y_range; i++)
	{
		for(int j=0; j<x_range; j++)
		{
			values[i*x_range+j]=(image[i+startLocation_y][j+startLocation_x])*(i+startLocation_y)*(j+startLocation_x);
			index_value[i*x_range+j]=(i+startLocation_y)*(j+startLocation_x); 
		}
	}
	
		
	for(int i=0; i<(int)values.size(); i++)
	{
		sum_xy+=(values[i]*index_value[i]);
		sum_x+=index_value[i];
		sum_y+=values[i];
		sum_x_squared+=(index_value[i])*index_value[i];
		sum_y_squared+=(values[i]*values[i]);
		
       	}

	
	result=(n*sum_xy-sum_x*sum_y)/(std::sqrt((n*sum_x_squared-sum_x*sum_x)*(n*sum_y_squared-sum_y*sum_y)));
	return result;
}
float mathFunctions::compute_distance(float x, float y)
{
	return std::sqrt(std::pow(x,2)+std::pow(y,2));
}


#endif
