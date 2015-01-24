
#ifndef DIVING_MASTER
#define DIVING_MASTER

#include "../drivers/PWM.h"
#include <memory>
#include <cassert>

/*
    Conventions:
        coordinate system is defined as:
            x: positive pointing right, negative pointing left relative to orientation
            y: positive pointing ahead, negative pointing behind relative to orientation
            z: positive pointing down, negative pointing up
*/

class DivingMaster
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

        static const int DEFAULT_SECONDS = 2;

        static DivingMaster& getInstance();

        void achieveXSpeed(float, int by = DEFAULT_SECONDS);
        void achieveYSpeed(float, int by = DEFAULT_SECONDS);
        void achieveZSpeed(float, int by = DEFAULT_SECONDS);

        void achievePitchRate(float, int by = DEFAULT_SECONDS);
        void achieveYawRate(float, int by = DEFAULT_SECONDS);
        void achieveRollRate(float, int by = DEFAULT_SECONDS);

    private:
        DivingMaster();
        ~DivingMaster();
        static DivingMaster* singleton_;

        static const uint PWM_PERIOD = 2000000;
        static const uint PWM_MIN = 1000000;
        static const uint PWM_MAX = 2000000;
        static const uint PWM_NEUTRAL = 1520000;

        std::shared_ptr<PWM> pwmX_;
        std::shared_ptr<PWM> pwmY_;
        std::shared_ptr<PWM> pwmZ_;

        void setXThrust(float);
        void setYThrust(float);
        void setZThrust(float);

        void setYawRate(float);  //positive means clockwise
        void setRollRate(float); //positive means clockwise

        void setLeftXThrust(float);
        void setRightXThrust(float);

        void setLeftYThrust(float);
        void setRightYThrust(float);

        void setLeftZThrust(float);
        void setRightZThrust(float);

        uint rateToDuty(float);
};

#endif
