/**
  * \class ThrustController
  *
  *  Created on: Jan 18, 2015
  *      Author: Jesse Victors
  *
  * \brief This is an API object designed as a way to provide a user with functions for controlling the active motion of the
  *        system via the thrusters. Functions range from common motion control to direct thruster access for advanced manual control.
  */

#ifndef DIVING_MASTER
#define DIVING_MASTER

#include <memory>
#include <chrono>
#include <cassert>
#include <cmath>
#include <thread>
#include <iostream>

#include "Drivers/PWM/PWM.h"

/*
    Conventions:
        coordinate system mirrors aerospace, so it is defined as:
            x: positive pointing ahead, negative pointing behind relative to orientation
            y: positive pointing right, negative pointing left relative to orientation
            z: positive pointing down, negative pointing up
*/

class ThrustController
{
    public:
        static constexpr float FULL_AHEAD = 1; ///< The value for the target thruster(s) at 100% throttle.
        static constexpr float NEUTRAL = 0; ///< The value to set the target thruster(s) to idle.
        static constexpr float FULL_REVERSE = -1; ///< The value to set the target thruster(s) at 100% reverse throttle.

        static const uint DEFAULT_SECONDS = 2; ///< Used for animated thruster motion.
        static const int UPDATE_DELAY_MS = 10; ///< Used as the animation frame-rate in thruster motion.
        static constexpr auto UPDATE_DELAY = std::chrono::milliseconds(UPDATE_DELAY_MS); ///< ?

        /** \brief Initializes a new instance of a motor-function interface.
          */
        ThrustController();
        ~ThrustController();

        /** \brief Sets the immediate forward-moving throttle speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active throttle.
          */
        void setForwardThrust(float);

        /** \brief Sets the immediate side-moving throttle speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active throttle.
          */
        void setStrafeThrust(float);

        /** \brief Sets the immediate rising-diving throttle speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active throttle.
          */
        void setDiveThrust(float);

        /** \brief Sets the immediate Z-axis-rotating (yaw) speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active angular acceleration.
          */
        void setYawThrust(float);

        /** \brief Sets the immediate X-axis-rotating (pitch) speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active angular acceleration.
          */
        void setPitchThrust(float, float);

        /** \brief Accelerates the forward-moving thrusters to a target throttle speed
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active throttle.
          * \param by The time in seconds for the throttle to reach the given goal.
          */
        void accelerateForward(float, uint by = DEFAULT_SECONDS);

        /** \brief Accelerates the side-moving thrusters to a target throttle speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active throttle.
          * \param by The time in seconds for the throttle to reach the given goal.
          */
        void accelerateStrafe(float, uint by = DEFAULT_SECONDS);

        /** \brief Accelerates the rising-diving thrusters to a target throttle speed.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active throttle.
          * \param by The time in seconds for the throttle to reach the given goal.
          */
        void accelerateDive(float, uint by = DEFAULT_SECONDS);

        /** \brief Displaces the current angular acceleration to a target acceleration.
          * \param goal A floating value ranging from -1 to 1 representing a percentage of the active angular acceleration.
          * \param by The time in seconds for the throttle to reach the given goal.
          */
        void accelerateYaw(float, uint by = DEFAULT_SECONDS);

    private:
        static const uint PWM_PERIOD = 2000000;
        static const uint PWM_MIN = 1000000;
        static const uint PWM_MAX = 2000000;
        static const uint PWM_NEUTRAL = 1520000;

        static constexpr float MIN_SEAB_POWER = 0.25f; //Seabotix min power to turn
        static constexpr float CANCEL_BRAKE_MIN = -0.3f; //cancel ESC braking

        static int instanceCount_;

        std::shared_ptr<PWM> pwmForward_;
        std::shared_ptr<PWM> pwmStrafe_;
        std::shared_ptr<PWM> pwmDive_;

        float leftForward_, rightForward_;
        float leftDrift_, rightDrift_;
        float leftDive_, rightDive_;

        // sets all thrusters to a given throttle speed
        void setAllThrust(float);

        // sets the left forward thruster to a given throttle speed
        void setLeftForwardThrust(float);
        // sets the right forward thruster to a given throttle speed
        void setRightForwardThrust(float);

        // sets the left side thruster to a given throttle speed
        void setLeftStrafeThrust(float);
        // sets the right side thruster to a given throttle speed
        void setRightStrafeThrust(float);

        // sets the left dive thruster to a given throttle speed
        void setLeftDiveThrust(float);
        // sets the right dive thruster to a given throttle speed
        void setRightDiveThrust(float);

        // converts a percentage into a PWM duty cycle
        // input: -100 % to 100 %; output 1,000,000 ns to 2,000,000 ns
        uint rateToDuty(float, bool) const;

        // returs an exponential value based on given:
        // target, initial position, and constant
        float logisticFn(float, float, float) const;
};

#endif
