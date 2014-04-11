#include "ros/ros.h"

#include "timer.h"


depthSensor()
{
	float pressure = 0.0;
	float tpressure = 0.0;
	int numVariables = 10;

	timer  pressureTimer;
	pressureTimer.start(1, 0);
	ros::Publisher pressurePub = nh.advertise<std_msgs::Float32>("Pressure_Data", 1000);
	int scanVal;
	 if ((scanfVal = sscanf(line.c_str(), "%f", &tpressure)) == numVariables)
	 {
		if (pressure != tpressure || pressureTimer.isTimeout())
		{
		    //depth
		    //gets pressure makes calculations on it
		   	std_msgs::Float32 pressureMsg;
			pressure = tpressure;
			pressureMsg.data = pressure;
			pressurePub.publish(pressureMsg);
			pressureTimer.start(1, 0);
			ros::spinOnce();
		}
		//return depth in inches
		return pressure;
	}
}