#include "ros/ros.h"
#include "../include/PidControllerLibrary/PidController.hpp"

/*
	A simple test program that shows how to use the pid controller with ros.
*/

int main(int argc, char ** argv)
{
	PIDController pid;
	pid.changeSetPoint(200);
		
	ros::init(argc, argv, "rosTest");
	ros::NodeHandle nodeHandle;	

	ros::Rate loop_rate(10);
	double input = 0.0;	

	while(ros::ok())
	{
		double out = pid.compute(input);
		input += 5*(out/255);	
		pid.printValues();
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return 0;
}
