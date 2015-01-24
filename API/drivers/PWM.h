/*
 * PWM.h
 *
 *  Created on: Jan 22, 2015
 *      Author: TekuConcept
 */

#ifndef PWM_H_
#define PWM_H_

#include "PWM_Const.h"
#include "Registry.h"

class PWM
{
    public:
        PWM(uint _addr_);

        // turn on / off the PWM submodule
        void start();
        void stop();

        // set the period for PWM channels A & B
        // return 0 for success
        // - units are in nanoseconds -
        int setPeriod(uint ns);

        // set the duty cycle for channel A
        // return 0 for success
        int setDutyA(uint ns);

        // set the duty cycle for channel B
        // return 0 for success
        int setDutyB(uint ns);

        // when polarity is 0, PWM will be toggled low
        // when trigger even occurs, 1 will toggle high
        void setPolarityA(uint dir);
        void setPolarityB(uint dir);

        uint getPeriod();
        uint getDutyA();
        uint getDutyB();
        uint getPolarityA();
        uint getPolarityB();

    private:
        Registry addr;
        uint period;
        uint dutyA;
        uint dutyB;
        uint cdiv;
        uint polA;
        uint polB;
};

#endif /* PWM_H_ */
