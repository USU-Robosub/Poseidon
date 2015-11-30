/**
  * \class HMC5883L
  *
  *  Created on: Jan 31, 2015
  *      Author: TekuConcept
  *
  * \brief This is a hardware wrapper for the HMC5883L compass sensor.
  *        It provides fundimental sensor readings and control in an orginized manner.
  */

#ifndef HMC5883L_H_
#define HMC5883L_H_

#include "IMU_Const.h"
#include "I2C/I2C.h"
#include <ICompass.h>
#include <stdexcept>


class HMC5883L : public ICompass
{
    public:
        /** \brief Initializes a new compass sensor for direction based analysis.
          * \param bus The address of the I2C bus the compass listens on.
          */
        HMC5883L(uint _bus_);
        ~HMC5883L();

        /** \brief Used to select the number of samples averaged per measurement output.
          */
        enum Sample
        { // Samples averaged per measurement
            Sx1, ///< 1 sample per measurement (default)
            Sx2, ///< 2 samples per measurement
            Sx4, ///< 4 samples per measurement
            Sx8  ///< 8 samples per measurement
        };

        /** \brief The Table below shows all selectable output rates in continuous measurement mode.
        *          All three channels shall be measured within a given output rate.
          */
        enum Rate
        { // Data Output Rate in Hertz
            Hz_75, ///< 0.75 Hz
            Hz1_5, ///< 1.50 Hz
            Hz3,   ///< 3.00 Hz
            Hz7_5, ///< 7.50 Hz
            Hz15,  ///< 15.00 Hz (Default)
            Hz30,  ///< 30.00 Hz
            Hz75   ///< 75.00 Hz
        };

        /** \brief Choose a lower gain value (higher GN#) when total field strength causes overflow
          *        in one of the data output registers (saturation). Output Range: -2048 - 2047
          */
        enum Gain
        { // Gain configuration in Gauss
            G_88, ///< ± 0.88 Ga
            G1_3, ///< ± 1.30 Ga (default)
            G1_9, ///< ± 1.90 Ga
            G2_5, ///< ± 2.50 Ga
            G4_0, ///< ± 4.00 Ga
            G4_7, ///< ± 4.70 Ga
            G5_6, ///< ± 5.60 Ga
            G8_1  ///< ± 8.10 Ga
        };

        /** \brief Used to select the operating mode of the device.
          */
        enum Mode
        { // Operating Mode
            /** \brief Continuous-Measurement Mode. In continuous-measurement mode,
              *        the device continuously performs measurements and places the
              *        result in the data register. RDY goes high when new data is placed
              *        in all three registers. After a power-on or a write to the mode or
              *        configuration register, the first measurement set is available from all
              *        three data output registers after a period of 2/fDO and subsequent
              *        measurements are available at a frequency of fDO, where fDO is the
              *        frequency of data output.
              */
            Continuous,

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

        /** \brief Sets the number of samples to be taken per measurement.
          * \param ma The provided sample rate value. Default = Sample.Sx1
          */
        void setSampleAverage(Sample ma);

        /** \brief Sets the rate in Hz at which data becomes available.
          * \param dor The provided data output rate value. Default = Rate.Hz15
          */
        void setOutputRate(Rate dor);

        /** \brief Sets the gain in Gauss applied to measurement samples.
          *        Note that the very first measurement after a gain change maintains the same gain as the previous setting.
          *        The new gain setting is effective from the second measurement and on.
          * \param gn The provided gain value. Default = Gain.G1_3
          */
        void setGain(Gain gn);

        /** \brief Sets the current operating mode. See the table for Mode for more information about the types of modes.
          * \param md The provided operating mode value. Default = Mode.Single
          */
        void setMode(Mode md);

        // sensor measurements
        /** \brief Reads the X-direction of the greatest polar field.
          * \return Returns a signed short value ranging from -2048 to 2047.
          */
        uint16_t X();

        /** \brief Reads the Y-direction of the greatest polar field.
          * \return Returns a signed short value ranging from -2048 to 2047.
          */
        uint16_t Y();

        /** \brief Reads the Z-direction of the greatest polar field.
          * \return Returns a signed short value ranging from -2048 to 2047.
          */
        uint16_t Z();

        // OO configuration access
        /** \brief Returns the last value set for the sample average.
          *        This is not always the same value read from the hardware's register.
          */
        uint getSampleAverage();

        /** \brief Returns the last value set for the output rate.
          *        This is not always the same value read from the hardware's register.
          */
        uint getOutputRate();

        /** \brief Returns the last value set for the gain.
          *        This is not always the same value read from the hardware's register.
          */
        uint getGain();

        /** \brief Returns the last value set for the mode.
          *        This is not always the same value read from the hardware's register.
          */
        uint getMode();

        /** \brief This flag indicates wether the data output register is currently locked.
          *        Reads from tri-axis data are still permitted.
          *        This flag is set when either:
          *        - Some but not all of the tri-axis data output registers have been read,
          *        - Mode register has been read. When this flag is set, the tri-axis data is
          *          locked and any new data will not be placed in these registers until one of
          *          these conditions are met:
          *          + All tri-axis data has been read,
          *          + The mode is changed,
          *          + The measurement configuration is changed,
          *          + Or power is reset.
          */
        bool isLocked();

        // this flag indicates that there is data ready to be read
        /** \brief This flag indicates tri-axis data is ready to be read.
          *        This flag is set when data is written to all 3 axis registers. It is cleared
          *        when the device initiates a write to the data output registers and after one
          *        or more of the data output registers are written to. When the ready flag is
          *        false, it shall remain flase for approximately 250 μs.
          */
        bool isReady();

    private:
        I2C bus;
        Sample samples;
        Rate outRate;
        Gain gain;
        Mode mode;
};

#endif /* HMC5883L_H_ */
