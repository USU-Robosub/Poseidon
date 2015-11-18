/**
  * \class PWM
  *
  *  Created on: Jan 22, 2015
  *      Author: TekuConcept
  *
  * \brief This class gives a programmer control over the pulse-width modulation subsystems and their respective channels.
  */

#ifndef PWM_H_
#define PWM_H_

#include "PWM_Const.h"
#include "Drivers/Registry.h"

class PWM
{
    public:
        /** \brief Initializes a specific PWM subsystem.
          * \param addr The address specifying the location of the subsystem.
          */
        PWM(uint _addr_);
        ~PWM();

        /** \brief Activates the signal such that the output will not be suppressed.
          */
        void start();
        
        /** \brief Deavtivates the signal such that the signal will be suppressed.
          */
        void stop();

        /** \brief Sets the amount of time to complete one pulse-width cycle
          *        The period applies to both channels A and B.
          * \param ns The time in nanoseconds
          * \return 0 for success
          */
        int setPeriod(uint ns);

        /** \brief Sets the amount of time a pulse is set on channel A before reseting.
          * \param ns The time in nanoseconds to hold the pulse.
          * \return 0 for sucess.
          */
        int setDutyA(uint ns);

        /** \brief Sets the amount of time a pulse is set on channel B before reseting.
          * \param ns The time in nanoseconds to hold the pulse.
          * \return 0 for sucess.
          */
        int setDutyB(uint ns);

        /** \brief Sets the polarity of the output on channel A.
          * \param dir When the polarity is set to 0, the pulse will be held low during the duty cycle.
          *            When the polarity is set to 1, the pulse will be held high.
          */
        void setPolarityA(uint dir);

        /** \brief Sets the polarity of the output on channel B.
          * \param dir When the polarity is set to 0, the pulse will be held low during the duty cycle.
          *            When the polarity is set to 1, the pulse will be held high.
          */
        void setPolarityB(uint dir);

        /** \brief Returns the last value set for the period.
          *        This is not always the same value read from the hardware's register.
          */
        uint getPeriod();

        /** \brief Returns the last value set for the duty of channel A.
          *        This is not always the same value read from the hardware's register.
          */
        uint getDutyA();

        /** \brief Returns the last value set for the duty of channel B.
          *        This is not always the same value read from the hardware's register.
          */
        uint getDutyB();

        /** \brief Returns the last value set for the polarity of channel A.
          *        This is not always the same value read from the hardware's register.
          */
        uint getPolarityA();

        /** \brief Returns the last value set for the polarity of channel B.
          *        This is not always the same value read from the hardware's register.
          */
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
