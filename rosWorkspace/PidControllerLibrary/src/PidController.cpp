#include "../include/PidControllerLibrary/PidController.hpp"

/*
 *The PID (proportional integral derivative) controller.
 *See PidTest.cpp for usage.
 */

PIDController::PIDController()
{
	initValues();	
}

PIDController::PIDController(double KP, double KI, double KD)
{
	initValues();
	this->KP = KP;
	this->KI = KI;
	this->KD = KD;
}

/*
These values were chosen based on analyzing data, etc.
*/
void PIDController::initValues()
{
	KP = 0.5;
	KI = 0.0;
	KD = 0.45;

	input = 0.0;
	setPoint = 0.0;
	lastTime = boost::posix_time::microsec_clock::local_time();	
	currentMode = AUTOMATIC;
	sampleTime = 1000.0;
	
	lastInput = 0.0;
	iTerm = 0.0;
	output = 0.0;
	outputMax = 255.0;
	outputMin = -255.0;
}

void PIDController::printValues()
{
	std::cout << "KP * error " <<  KP * error << std::endl;
	std::cout << "iTerm " << iTerm << std::endl;	
	std::cout << "KD * dInput " << KD * dInput << std::endl;
	std::cout << "Error " << error << std::endl;
	std::cout << "Input " << input << std::endl;
	std::cout << "Set point " << setPoint << std::endl;
	std::cout << "Output " << output << std::endl << std::endl;
}

/*
A simple clamp function that clamps a value between the min and max provided.
*/
void PIDController::clampValues(double & value, double min, double max)
{
	if(value > max)
		value = max;
	else if(value < min)
		value = min;	
}

//Update the appropriate values when the PID controller is switched from MANUAL to AUTOMATIC.
//All values which must be set when switching the pid controller from MANUAL to AUTOMATIC go here.
void PIDController::updateValues(double input)
{
	lastInput = input;
}

/*
When switching the pid controller from MANUAL to AUTOMATIC, we must provide an input based on the current state of the sub. 
That is the location, speed, etc of the sub.
Forgetting to set the input can cause a disruption in the output of the pid controller due to the value of lastInput no longer being relavent.
*/
void PIDController::switchPIDState(double input)
{
	switch(currentMode)
	{
		case AUTOMATIC:
			currentMode = MANUAL;
			break;
		case MANUAL:
			currentMode = AUTOMATIC;
			updateValues(input);
			break;
	}
}

void PIDController::setLimits(double outputMin, double outputMax)
{
	if(outputMin > outputMax) 
		return;

	this->outputMin = outputMin;
	this->outputMax = outputMax;	
	//Clamp the stored values incase they are no longer relevant.	
	clampValues(this->output, outputMin, outputMax);
	clampValues(this->iTerm, outputMin, outputMax);
}

void PIDController::setTunnings(double KP, double KI, double KD)
{
	double sampleTimeSeconds = sampleTime / milliInSeconds;
	this->KP = KP;
	//Since we are calling the PID algorithm at a regular interval, we can simplify the math by calculating KI and KD with the time value.
	this->KI = KI * sampleTimeSeconds;
	this->KD = KD / sampleTimeSeconds;
}

/*
When the sample time is changed during run time we must update KI and KD properly as not to change the meaning of KI and KD. 
*/
void PIDController::setSampleTime(double newSampleTime)
{
	if(newSampleTime > 0)
	{
		double ratio = newSampleTime / sampleTime;
		KI *= ratio;
		KD /= ratio;
		sampleTime = newSampleTime;
	}
}

double PIDController::compute(double input)
{
	if(currentMode == MANUAL) return output;
	
	boost::posix_time::time_duration elapsedTime = boost::posix_time::microsec_clock::local_time() - lastTime;

	if(elapsedTime.total_milliseconds() >= sampleTime) 
	{
		this->input = input;

		error = setPoint - input;
		//Here we factor KI into the the integral.
		//This allows us to avoid an increase in the output when KI changes. 
		//Otherwise, when KI changes the entire error sum will multiplied by the new factor.
		//This way only the errors which accumulate from the change on will be affected by the new factor.
		iTerm += error * KI;
		clampValues(iTerm, outputMin, outputMax);
		
		//Here we take the derivative of the input instead of the error.
		//We get the same result once we negate dInput. 
		//However, when the setpoint changs we no longer recieve a sudden change in the derivative.
 	 	dInput = (input - lastInput);
		output = KP * error + iTerm - KD * dInput;
		clampValues(output, outputMin, outputMax);

		lastInput = input;
		lastTime = boost::posix_time::microsec_clock::local_time();
	}
	return output;
}
