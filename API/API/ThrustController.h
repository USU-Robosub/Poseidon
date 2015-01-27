
#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "../drivers/PWM.h"
#include <memory>
#include <chrono>
#include <cassert>

/*
    Conventions:
        coordinate system is defined as:
            x: positive pointing right, negative pointing left relative to orientation
            y: positive pointing ahead, negative pointing behind relative to orientation
            z: positive pointing down, negative pointing up
*/

class ThrustController
{
    public:
        static constexpr float FULL_AHEAD = 1;
        static constexpr float TWO_THIRDS_AHEAD = 2 / 3.0f;
        static constexpr float HALF_AHEAD = 1 / 2.0f;
        static constexpr float ONE_THIRD_AHEAD = 1 / 3.0f;
        static constexpr float NEUTRAL = 0;
        static constexpr float ONE_THIRD_REVERSE = -1 / 3.0f;
        static constexpr float HALF_REVERSE = -1 / 2.0f;
        static constexpr float TWO_THIRDS_REVERSE = -2 / 3.0f;
        static constexpr float FULL_REVERSE = -1;

        static const uint DEFAULT_SECONDS = 2;
        static constexpr float PRECISION = 1 / 64.0f;

        static const int UPDATE_DELAY_MS = 25;
        static constexpr auto UPDATE_DELAY = std::chrono::milliseconds(UPDATE_DELAY_MS);

        struct ThrustVector
        {
            ThrustVector():
                ThrustVector(0)
            {}

            ThrustVector(float val):
                ThrustVector(val, val, val)
            {}

            ThrustVector(float x, float y, float z):
                x_(x), y_(y), z_(z)
            {}

            float x_, y_, z_;
        };

        ThrustController();
        ~ThrustController();

        //void achieveThrustVector(ThrustVector, uint by = DEFAULT_SECONDS);
        void achieveXRate(float, uint by = DEFAULT_SECONDS);
        void achieveYRate(float, uint by = DEFAULT_SECONDS);
        void achieveZRate(float, uint by = DEFAULT_SECONDS);

        void achieveYawRate(float, uint by = DEFAULT_SECONDS);
        void achieveRollRate(float, uint by = DEFAULT_SECONDS);

    private:
        static const uint PWM_PERIOD = 2000000;
        static const uint PWM_MIN = 1000000;
        static const uint PWM_MAX = 2000000;
        static const uint PWM_NEUTRAL = 1520000;

        static int instanceCount_;

        std::shared_ptr<PWM> pwmX_;
        std::shared_ptr<PWM> pwmY_;
        std::shared_ptr<PWM> pwmZ_;

        ThrustVector leftThrusters_;
        ThrustVector rightThrusters_;

        void setAllThrust(float);

        void setLeftXThrust(float);
        void setRightXThrust(float);

        void setLeftYThrust(float);
        void setRightYThrust(float);

        void setLeftZThrust(float);
        void setRightZThrust(float);

        uint rateToDuty(float);
        float logisticFn(float, float, float);
};

#endif
