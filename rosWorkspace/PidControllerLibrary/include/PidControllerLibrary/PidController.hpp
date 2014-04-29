#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include <iostream>

class PIDController
{

private:
	//Helper Functions
	void clampValues(double & value, double min, double max);
	void updateValues(double input);//Called when the PID is switched from MANUAL to AUTOMATIC
	void initValues();//Called from the constructors.	
	//Private members
	static const int milliInSeconds = 1000;
	enum mode {MANUAL, AUTOMATIC};//The states that the PID controller can be in. 
	mode currentMode;//Used to control whihc mode the PID controller is in.
	double KP;//K-proportional is a tuning value for the proportional portion.
	double KI;//K-integral is a tuning value for the integral portion.
	double KD;//K-derivative is a tuning value for the derivative portion.
	double error;//The error which is the difference between the setpoint and the input.
	double setPoint;//This is the desired location or speed of the sub.
	double input;//The is the current speed or location of the sub.
	double dInput;//The derivative of the input.
	boost::posix_time::ptime lastTime;//Used to keep track of elapsed time.
	double sampleTime;//Used to call the algorithm at a fixed rate. This allows us to make the math simplier.
	double lastInput;//Used in KD to avoid derivative kick which occurs when the setpoint changes.
	double iTerm;//The integral term is used to avoid bumps in the input when changing KI at runtime.
	double output;//Output value of the PID algorithm
	double outputMax;//This value is used to clamp the output so that it doesn't go above a desired maximum.
	double outputMin;//This is used to clamp the output so that it doesn't go below a desired minimum.

public:
	//Constructors
	PIDController();
	PIDController(double KP, double KI, double KD);
	//Setters
	void setLimits(double outputMin, double outputMax);
	void setTunnings(double KP, double KI, double KD);
	void setSampleTime(double newSampleTime);	
	void changeSetPoint(double setPoint) {this->setPoint = setPoint;}
	//Getters
	double getOutputMin() {return outputMin;}
	double getOutputMax() {return outputMax;}
	double getKP() {return KP;}
	double getKI() {return KI;}
	double getKD() {return KD;}
	double getSetPoint() {return setPoint;}
	double getSampleTimeSeconds() {return sampleTime / milliInSeconds;}	
	double getSampleTime() {return sampleTime;}
	double getInput() {return input;}
	double getLastInput() {return lastInput;}
	mode getState() {return currentMode;}	
	//Workhorse functions	
	void switchPIDState(double input);
	double compute(double input);
	void printValues();
};

#endif
