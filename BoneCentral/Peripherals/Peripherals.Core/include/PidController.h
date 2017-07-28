//
// Created by nfcop on 7/15/2017.
//

#ifndef PERIPHERALS_PID_CONTROLLER_H
#define PERIPHERALS_PID_CONTROLLER_H

class PidController {

private:
    float previousError_;
    float min_;
    float max_;
    float p_;
    float i_;
    float d_;
    float integral_;
    float timeDelta_;

public:

    struct Configuration {
        float P;
        float I;
        float D;
    };

    PidController() : previousError_(0.0f), integral_(0.0f) {}

    /**
     * Configures constants.
     * @param configuration
     * @return `this` for chaining
     */
    PidController& withConstants(Configuration configuration);

    /**
     * Configures bounds. The adjustment returned will always be within these bounds
     * @param minimum
     * @param maximum
     * @return `this` for chaining
     */
    PidController& withBounds(float minimum, float maximum);

    /**
     * Configure the time delta between updates.
     * @param timeDelta in milliseconds
     * @return `this` for chaining
     */
    PidController& withTimeDelta(unsigned int timeDelta);

    /**
     * Calculates the current adjustment needed
     * Attention: this function contains a side-effect: updates the running error
     * @param setPoint the target value
     * @param processValue the current sensor reading
     * @return the adjustment to send to the motors, servo, etc.
     */
    float calculateAdjustmentFor(float setPoint, float processValue);

};


#endif //PERIPHERALS_PID_CONTROLLER_H
