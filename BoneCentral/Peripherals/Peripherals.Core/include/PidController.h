//
// Created by nfcop on 7/15/2017.
//

#ifndef PERIPHERALS_PID_CONTROLLER_H
#define PERIPHERALS_PID_CONTROLLER_H


class PidController {

private:
    double previousError_;
    double min_;
    double max_;
    double p_;
    double i_;
    double d_;
    double timeDelta_;

public:

    PidController() : previousError_(0.0) {}

    /**
     * Configures constants.
     * @param p the Proportion constant
     * @param i the Integral constant
     * @param d the Derivative constant
     * @return `this` for chaining
     */
    PidController& withConstants(double p, double i, double d);

    /**
     * Configures bounds. The adjustment returned will always be within these bounds
     * @param minimum
     * @param maximum
     * @return `this` for chaining
     */
    PidController& withBounds(double minimum, double maximum);

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
    double calculateAdjustmentFor(double setPoint, double processValue);

};


#endif //PERIPHERALS_PID_CONTROLLER_H
