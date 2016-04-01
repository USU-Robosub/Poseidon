#ifndef IMU_POWER_H
#define IMU_POWER_H

#include <MPU6050.h>
#include <HMC5883.h>
#include <IImuPower.h>

enum class Mode { // Operating Mode
    /** \brief Continuous-Measurement Mode. In continuous-measurement mode,
      *        the device continuously performs measurements and places the
      *        result in the data register. RDY goes high when new data is placed
      *        in all three registers. After a power-on or a write to the mode or
      *        configuration register, the first measurement set is available from all
      *        three data output registers after a period of 2/fDO and subsequent
      *        measurements are available at a frequency of fDO, where fDO is the
      *        frequency of data output.
      */
    Continuous=0,

    /** \brief Single-Measurement Mode (Default). When single-measurement
      *        mode is selected, device performs a single measurement, sets RDY
      *        high and returned to idle mode. Mode register returns to idle mode
      *        bit values. The measurement remains in the data output register and
      *        RDY remains high until the data output register is read or another
      *        measurement is performed.
      */
    Single,

    /** \brief Idle Mode. Device is placed in idle mode.
      */
    Idle,
};

class ImuPower : IImuPower
{
private:
	std::shared_ptr<MPU6050> accelerometer_;
	std::shared_ptr<HMC5883> compass_;
public:
	ImuPower(std::shared_ptr<MPU6050> accelerometer, std::shared_ptr<HMC5883> compass);
	void sleep();
	void wake();
};

#endif