/*
 * HMC5883L.h
 *
 *  Created on: Jan 31, 2015
 *      Author: TekuConcept
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

#include "IMU_Const.h"
#include "../I2C/I2C.h"
#include "stdint.h"
#include <stdexcept>


class HMC5883L
{
    public:
        HMC5883L(uint _bus_);
        virtual ~HMC5883L();

        // Samples averaged per measurement
        enum Sample
        {
            Sx1, Sx2,
            Sx4, Sx8
        };

        // Data Output Rate in Hertz
        enum Rate
        {
            Hz_75, Hz1_5,
            Hz3,   Hz7_5,
            Hz15,  Hz30,
            Hz75
        };

        // Gain configuration in Gauss
        enum Gain
        {
            G_88, G1_3,
            G1_9, G2_5,
            G4_0, G4_7,
            G5_6, G8_1
        };

        // Operating Mode
        enum Mode
        {
            /*
            In continuous-measurement mode,
            the device continuously performs measurements and places the
            result in the data register. RDY goes high when new data is placed
            in all three registers.
             */
            Continuous,

            /*
            When single-measurement mode is selected, device performs a single
            measurement, sets RDY high and returns to idle mode.
             */
            Single,

            /*
            Device is placed in idle mode.
             */
            Idle,
        };

        // set the number of samples to be taken for accuracy
        void setSampleAverage(Sample ma); // - default: Sample.Sx1  -

        // set the rate in Hz at which data becomes available
        void setOutputRate(Rate dor);     // - default: Rate.Hz15   -

        // Choose a lower gain value (higher GN#) when total field
        // strength causes overflow in one of the data output registers
        // (saturation). Note that the very first measurement after a
        // gain change maintains the same gain as the previous setting.
        void setGain(Gain gn);            // - default: Gain.G1_3   -

        // set the current operating mode of the device
        void setMode(Mode md);            // - default: Mode.Single -

        // sensor measurements
        uint16_t X();
        uint16_t Y();
        uint16_t Z();

        // OO configuration access
        uint getSampleAverage();
        uint getOutputRate();
        uint getGain();
        uint getMode();

        // this flag indicates whether the data output register is
        // currently locked - this does not affect reads
        bool isLocked();

        // this flag indicates that there is data ready to be read
        bool isReady();

    private:
        I2C bus;
        Sample samples;
        Rate outRate;
        Gain gain;
        Mode mode;
};

#endif /* HMC5883L_H_ */
