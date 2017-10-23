/**
  * \class HMC5883L
  *
  *  Created on: March 6, 2016
  *      Author: TekuConcept
  *
  * \brief A comprehensive list of slave register addresses.
  */

#ifndef HMC5883L_REG_H_
#define HMC5883L_REG_H_

// --- HMC5883L --- http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf
#define HMC5883L_ADDR            0x1E
#define HMC5883L_CONFIG_A        0x00 // r / w       0x10        [7] reserved        [6] sample count    [5] sample count    [4] output rate     [3] output rate     [2] output rate     [1] measure config  [0] measure config
#define HMC5883L_CONFIG_B        0x01 // r / w       0x20        [7] gain            [6] gain            [5] gain            [4] reserved        [3] reserved        [2] reserved        [1] reserved        [0] reserved
#define HMC5883L_MODE            0x02 // r / w       0x01        [7] High Speed      [6] reserved        [5] reserved        [4] reserved        [3] reserved        [2] reserved        [1] mode select     [0] mode select     (0: Continuous  1: Single   2|3: Idle)
#define HMC5883L_X_H             0x03 // r           0x00
#define HMC5883L_X_L             0x04 // r           0x00
#define HMC5883L_Z_H             0x05 // r           0x00
#define HMC5883L_Z_L             0x06 // r           0x00
#define HMC5883L_Y_H             0x07 // r           0x00
#define HMC5883L_Y_L             0x08 // r           0x00
#define HMC5883L_STATUS          0x09 // r           0x00        [7] reserved        [6] reserved        [5] reserved        [4] reserved        [3] reserved        [2] reserved        [1] LOCK            [0] RDY
#define HMC5883L_ID_A            0x0A // r           0x48
#define HMC5883L_ID_B            0x0B // r           0x34
#define HMC5883L_ID_C            0x0C // r           0x33

#endif