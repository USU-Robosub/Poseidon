
#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "../drivers/PWM/PWM.h"
#include <memory>
#include <chrono>
#include <cassert>

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
        static constexpr float FULL_AHEAD = 1;
        static constexpr float NEUTRAL = 0;
        static constexpr float FULL_REVERSE = -1;

        static const uint DEFAULT_SECONDS = 2;
        static const int UPDATE_DELAY_MS = 10;
        static constexpr auto UPDATE_DELAY = std::chrono::milliseconds(UPDATE_DELAY_MS);

        ThrustController();
        ~ThrustController();

        void setForwardThrust(float);
        void setDriftThrust(float);
        void setDiveThrust(float);
        void setYawThrust(float);

        void accelerateForward(float, uint by = DEFAULT_SECONDS);
        void accelerateDrift(float, uint by = DEFAULT_SECONDS);
        void accelerateDive(float, uint by = DEFAULT_SECONDS);
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
        std::shared_ptr<PWM> pwmDrift_;
        std::shared_ptr<PWM> pwmDive_;

        float leftForward_, rightForward_;
        float leftDrift_, rightDrift_;
        float leftDive_, rightDive_;

        void setAllThrust(float);

        void setLeftForwardThrust(float);
        void setRightForwardThrust(float);

        void setLeftDriftThrust(float);
        void setRightDriftThrust(float);

        void setLeftDiveThrust(float);
        void setRightDiveThrust(float);

        uint rateToDuty(float, bool) const;
        float logisticFn(float, float, float) const;
};

#endif
