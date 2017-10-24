//
// Created by nfcop on 7/15/2017.
//

#ifndef PERIPHERALS_PID_CONTROLLER_H
#define PERIPHERALS_PID_CONTROLLER_H

#include <atomic>
#include <thread>
#include <mutex>
#include <unistd.h>

class PidController {

private:
    float previousError_;
    float min_;
    float max_;
    float p_;
    float i_;
    float d_;
    float integral_;
    std::atomic<unsigned int> timeDelta_;

    std::thread* thread_;
    std::atomic<bool> stop_;

    float setPoint_;
    std::mutex setPointMutex_;
    
    void (*setControlValue)(float); //this->setControlValue(value);
    float (*getProcessValue)(void);

    void run();
    
    /**
     * Calculates the current adjustment needed
     * Attention: this function contains a side-effect: updates the running error
     * @param setPoint the target value
     * @param processValue the current sensor reading
     * @return the adjustment to send to the motors, servo, etc.
     */
    float calculateAdjustmentFor(float setPoint, float processValue);

public:

    struct Configuration {
        float P;
        float I;
        float D;
    };

    PidController() 
	: previousError_(0.0f)
	, integral_(0.0f)
	, setControlValue([](float val){val++;})
	, getProcessValue([](){return 0.0f;})
	{}

    /**
     * Configures constants.
     * @param configuration
     * @return `this` for chaining
     */
    PidController& withConstants(Configuration configuration);

    /**
     * Configures constants.
     * @param configuration
     * @return `this` for chaining
     */
    PidController& withTimeDelta(unsigned int timeDelta);

    /**
     * Configures bounds. The adjustment returned will always be within these bounds
     * @param processValueFunction
     * @param controlValueFunction
     * @return `this` for chaining
     */
    PidController& withBounds(float processValueFunction, float controlValueFunction);

    /**
     * Configures functions to be used for getting process value and setting control value
     * @param set
     * @param maximum
     * @return `this` for chaining
     */
    PidController& withFunctions(float (*processValueFunction)(void), void (*controlValueFunction)(float));
	

    /**
     * Updates setpoint.  The set point will be used the next PID cycle.
     * @param setpoint
     * @return `this` for chaining
     */
    PidController& updateSetPoint(float setPoint);

    /**
     * Start the PID Controller
     * @return `this` for chaining
     */
    PidController& start();
    
    /**
     * Stops the PID Controller
     * @return `this` for chaining
     */
    PidController& stop();
};


#endif //PERIPHERALS_PID_CONTROLLER_H
