#define CMPR_ADDR    0x03 ///< Address of the power module device.
#define CMPR_SYSV    0x00 ///< Address for the software version of the device.
#define CMPR_SYSS    0x01 ///< Address for the status of the system. [0=>"free", 1=>"busy"]
#define CMPR_THST    0x02 ///< Address for the thrusters' relay control board register.
#define CMPR_SLED    0x03 ///< Address for the LED light strip color register.
#define CMPR_A_HI    0x04 ///< Address for the high end byte of an analog read on ADC 1.
#define CMPR_A_LO    0x05 ///< Address for the low end byte of an analog read on ADC 1.
#define CMPR_B_HI    0x06 ///< Address for the high end byte of an analog read on ADC 2.
#define CMPR_B_LO    0x07 ///< Address for the low end byte of an analog read on ADC 2.
#define CMPR_C_HI    0x08 ///< Address for the high end byte of an analog read on ADC 3.
#define CMPR_C_LO    0x09 ///< Address for the low end byte of an analog read on ADC 3.
#define CMPR_D_HI    0x0A ///< Address for the high end byte of a digital read on ADC 4.
#define CMPR_D_LO    0x0B ///< Address for the low end byte of a digital read on ADC 4.
#define CMPR_READ    0x0D ///< Address where the master can select the register to read from