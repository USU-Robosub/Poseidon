/**
  * \class BMP085
  *
  *  Created on: Jan 29, 2015
  * Last Edited: Feb  7, 2016
  *      Author: TekuConcept
  *
  * \brief A comprehensive list of slave register addresses.
  */

#ifndef IMU_CONST_H_
#define IMU_CONST_H_

//      NAME                        REGISTER            DEFAULT     NOTE
// --- HMC5883L --- http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf
#define IMU_COMPASS_ADDR            0x1E
#define IMU_COMPASS_CONFIG_A        0x00 // r / w       0x10        [7] reserved        [6] sample count    [5] sample count    [4] output rate     [3] output rate     [2] output rate     [1] measure config  [0] measure config
#define IMU_COMPASS_CONFIG_B        0x01 // r / w       0x20        [7] gain            [6] gain            [5] gain            [4] reserved        [3] reserved        [2] reserved        [1] reserved        [0] reserved
#define IMU_COMPASS_MODE            0x02 // r / w       0x01        [7] High Speed      [6] reserved        [5] reserved        [4] reserved        [3] reserved        [2] reserved        [1] mode select     [0] mode select     (0: Continuous  1: Single   2|3: Idle)
#define IMU_COMPASS_X_H             0x03 // r           0x00
#define IMU_COMPASS_X_L             0x04 // r           0x00
#define IMU_COMPASS_Z_H             0x05 // r           0x00
#define IMU_COMPASS_Z_L             0x06 // r           0x00
#define IMU_COMPASS_Y_H             0x07 // r           0x00
#define IMU_COMPASS_Y_L             0x08 // r           0x00
#define IMU_COMPASS_STATUS          0x09 // r           0x00        [7] reserved        [6] reserved        [5] reserved        [4] reserved        [3] reserved        [2] reserved        [1] LOCK            [0] RDY
#define IMU_COMPASS_ID_A            0x0A // r           0x48
#define IMU_COMPASS_ID_B            0x0B // r           0x34
#define IMU_COMPASS_ID_C            0x0C // r           0x33

// --- MPU6050 --- http://invensense.com/mems/gyro/documents/RM-MPU-6000A.pdf
#define IMU_MOTION_ADDR_A           0x68 //
#define IMU_MOTION_ADDR_B           0x69 //
#define IMU_MOTION_SELF_TEST_X      0x0D // r / w                   [7] XA_TEST         [6] XA_TEST         [5] XA_TEST         [4] XG_TEST         [3] XG_TEST         [2] XG_TEST         [1] XG_TEST         [0] XG_TEST
#define IMU_MOTION_SELF_TEST_Y      0x0E // r / w                   [7] YA_TEST         [6] YA_TEST         [5] YA_TEST         [4] YG_TEST         [3] YG_TEST         [2] YG_TEST         [1] YG_TEST         [0] YG_TEST
#define IMU_MOTION_SELF_TEST_Z      0x0F // r / w                   [7] ZA_TEST         [6] ZA_TEST         [5] ZA_TEST         [4] ZG_TEST         [3] ZG_TEST         [2] ZG_TEST         [1] ZG_TEST         [0] ZG_TEST
#define IMU_MOTION_SELF_TEST_A      0x10 // r / w                   [7] reserved        [6] reserved        [5] XA_TEST         [4] XA_TEST         [3] YA_TEST         [2] YA_TEST         [1] ZA_TEST         [0] ZA_TEST
#define IMU_MOTION_SMPLRT_DIV       0x19 // r / w
#define IMU_MOTION_CONFIG           0x1A // r / w                   [7] reserved        [6] reserved        [5] EXT_SYNC_SET    [4] EXT_SYNC_SET    [3] EXT_SYNC_SET    [2] DLPF_CFG        [1] DLPF_CFG        [0] DLPF_CFG
#define IMU_MOTION_GYRO_CONFIG      0x1B // r / w                   [7] reserved        [6] reserved        [5] reserved        [4] FS_SEL          [3] FS_SEL          [2] reserved        [1] reserved        [0] reserved
#define IMU_MOTION_ACCEL_CONFIG     0x1C // r / w                   [7] XA_ST           [6] YA_ST           [5] ZA_ST           [4] AFS_SEL         [3] AFS_SEL         [2] reserved        [1] reserved        [0] reserved
#define IMU_MOTION_MOT_THR          0x1F // r / w
#define IMU_MOTION_FIFO_EN          0x23 // r / w                   [7] TEMP_FIFO_EN    [6] XG_FIFO_EN      [5] YG_FIFO_EN      [4] ZG_FIFO_EN      [3] ACCEL_FIFO_EN   [2] SLV2_FIFO_EN    [1] SLV1_FIFO_EN    [0] SLV0_FIFO_EN
#define IMU_MOTION_I2C_MST_CTRL     0x24 // r / w                   [7] MULT_MST_EN     [6] WAIT_FOR_ES     [5] SLV3_FIFO_EN    [4] I2C_MST_P_NSR   [3] I2C_MST_CLK     [2] I2C_MST_CLK     [1] I2C_MST_CLK     [0] I2C_MST_CLK
#define IMU_MOTION_I2C_SLV0_ADDR    0x25 // r / w                   [7] I2C_SLV0_RW     [6] I2C_SLV0_ADDR   [5] I2C_SLV0_ADDR   [4] I2C_SLV0_ADDR   [3] I2C_SLV0_ADDR   [2] I2C_SLV0_ADDR   [1] I2C_SLV0_ADDR   [0] I2C_SLV0_ADDR
#define IMU_MOTION_I2C_SLV0_REG     0x26 // r / w
#define IMU_MOTION_I2C_SLV0_CTRL    0x27 // r / w                   [7] I2C_SLV0_EN     [6] I2C_SLV0_BYTE_SW[5] I2C_SLV0_REG_DIS[4] I2C_SLV0_GRP    [3] I2C_SLV0_LEN    [2] I2C_SLV0_LEN    [1] I2C_SLV0_LEN    [0] I2C_SLV0_LEN
#define IMU_MOTION_I2C_SLV1_ADDR    0x28 // r / w                   [7] I2C_SLV1_RW     [6] I2C_SLV1_ADDR   [5] I2C_SLV1_ADDR   [4] I2C_SLV1_ADDR   [3] I2C_SLV1_ADDR   [2] I2C_SLV1_ADDR   [1] I2C_SLV1_ADDR   [0] I2C_SLV1_ADDR
#define IMU_MOTION_I2C_SLV1_REG     0x29 // r / w
#define IMU_MOTION_I2C_SLV1_CTRL    0x2A // r / w                   [7] I2C_SLV1_EN     [6] I2C_SLV1_BYTE_SW[5] I2C_SLV1_REG_DIS[4] I2C_SLV1_GRP    [3] I2C_SLV1_LEN    [2] I2C_SLV1_LEN    [1] I2C_SLV1_LEN    [0] I2C_SLV1_LEN
#define IMU_MOTION_I2C_SLV2_ADDR    0x2B // r / w                   [7] I2C_SLV2_RW     [6] I2C_SLV2_ADDR   [5] I2C_SLV2_ADDR   [4] I2C_SLV2_ADDR   [3] I2C_SLV2_ADDR   [2] I2C_SLV2_ADDR   [1] I2C_SLV2_ADDR   [0] I2C_SLV2_ADDR
#define IMU_MOTION_I2C_SLV2_REG     0x2C // r / w
#define IMU_MOTION_I2C_SLV2_CTRL    0x2D // r / w                   [7] I2C_SLV2_EN     [6] I2C_SLV2_BYTE_SW[5] I2C_SLV2_REG_DIS[4] I2C_SLV2_GRP    [3] I2C_SLV2_LEN    [2] I2C_SLV2_LEN    [1] I2C_SLV2_LEN    [0] I2C_SLV2_LEN
#define IMU_MOTION_I2C_SLV3_ADDR    0x2E // r / w                   [7] I2C_SLV3_RW     [6] I2C_SLV3_ADDR   [5] I2C_SLV3_ADDR   [4] I2C_SLV3_ADDR   [3] I2C_SLV3_ADDR   [2] I2C_SLV3_ADDR   [1] I2C_SLV3_ADDR   [0] I2C_SLV3_ADDR
#define IMU_MOTION_I2C_SLV3_REG     0x2F // r / w
#define IMU_MOTION_I2C_SLV3_CTRL    0x30 // r / w                   [7] I2C_SLV3_EN     [6] I2C_SLV3_BYTE_SW[5] I2C_SLV3_REG_DIS[4] I2C_SLV3_GRP    [3] I2C_SLV3_LEN    [2] I2C_SLV3_LEN    [1] I2C_SLV3_LEN    [0] I2C_SLV3_LEN
#define IMU_MOTION_I2C_SLV4_ADDR    0x31 // r / w                   [7] I2C_SLV4_RW     [6] I2C_SLV4_ADDR   [5] I2C_SLV4_ADDR   [4] I2C_SLV4_ADDR   [3] I2C_SLV4_ADDR   [2] I2C_SLV4_ADDR   [1] I2C_SLV4_ADDR   [0] I2C_SLV4_ADDR
#define IMU_MOTION_I2C_SLV4_REG     0x32 // r / w
#define IMU_MOTION_I2C_SLV4_DO      0x33 // r / w
#define IMU_MOTION_I2C_SLV4_CTRL    0x34 // r / w                   [7] I2C_SLV4_EN     [6] I2C_SLV4_INT_EN [5] I2C_SLV4_REG_DIS[4] I2C_MST_DLY     [3] I2C_MST_DLY     [2] I2C_MST_DLY     [1] I2C_MST_DLY     [0] I2C_MST_DLY
#define IMU_MOTION_I2C_SLV4_DI      0x35 // r
#define IMU_MOTION_I2C_MST_STATUS   0x36 // r                       [7] PASS_THROUGH    [6] I2C_SLV4_DONE   [5] I2C_LOST_ARB    [4] I2C_SLV4_NACK   [3] I2C_SLV3_NACK   [2] I2C_SLV2_NACK   [1] I2C_SLV1_NACK   [0] I2C_SLV0_NACK
#define IMU_MOTION_INT_PIN_CFG      0x37 // r / w                   [7] INT_LEVEL       [6] INT_OPEN        [5] LATCH_INT_EN    [4] INT_RD_CLEAR    [3] FSYNC_INT_LEVEL [2] FSYNC_INT_EN    [1] I2C_BYPASS_EN   [0] reserved
#define IMU_MOTION_INT_ENABLE       0x38 // r / w                   [7] reserved        [6] MOT_EN          [5] reserved        [4] FIFO_OFLOW_EN   [3] I2C_MST_INT_EN  [2] reserved        [1] reserved        [0] DATA_RDY_EN
#define IMU_MOTION_INT_STATUS       0x3A // r                       [7] reserved        [6] MOT_INT         [5] reserved        [4] FIFO_OFLOW_INT  [3] I2C_MST_INT     [2] reserved        [1] reserved        [0] DATA_RDY_INT
#define IMU_MOTION_ACCEL_XOUT_H     0x3B // r
#define IMU_MOTION_ACCEL_XOUT_L     0x3C // r
#define IMU_MOTION_ACCEL_YOUT_H     0x3D // r
#define IMU_MOTION_ACCEL_YOUT_L     0x3E // r
#define IMU_MOTION_ACCEL_ZOUT_H     0x3F // r
#define IMU_MOTION_ACCEL_ZOUT_L     0x40 // r
#define IMU_MOTION_TEMP_OUT_H       0x41 // r
#define IMU_MOTION_TEMP_OUT_L       0x42 // r
#define IMU_MOTION_GYRO_XOUT_H      0x43 // r
#define IMU_MOTION_GYRO_XOUT_L      0x44 // r
#define IMU_MOTION_GYRO_YOUT_H      0x45 // r
#define IMU_MOTION_GYRO_YOUT_L      0x46 // r
#define IMU_MOTION_GYRO_ZOUT_H      0x47 // r
#define IMU_MOTION_GYRO_ZOUT_L      0x48 // r
#define IMU_MOTION_EXT_SENS_DATA_00 0x49 // r
#define IMU_MOTION_EXT_SENS_DATA_01 0x4A // r
#define IMU_MOTION_EXT_SENS_DATA_02 0x4B // r
#define IMU_MOTION_EXT_SENS_DATA_03 0x4C // r
#define IMU_MOTION_EXT_SENS_DATA_04 0x4D // r
#define IMU_MOTION_EXT_SENS_DATA_05 0x4E // r
#define IMU_MOTION_EXT_SENS_DATA_06 0x4F // r
#define IMU_MOTION_EXT_SENS_DATA_07 0x50 // r
#define IMU_MOTION_EXT_SENS_DATA_08 0x51 // r
#define IMU_MOTION_EXT_SENS_DATA_09 0x52 // r
#define IMU_MOTION_EXT_SENS_DATA_10 0x53 // r
#define IMU_MOTION_EXT_SENS_DATA_11 0x54 // r
#define IMU_MOTION_EXT_SENS_DATA_12 0x55 // r
#define IMU_MOTION_EXT_SENS_DATA_13 0x56 // r
#define IMU_MOTION_EXT_SENS_DATA_14 0x57 // r
#define IMU_MOTION_EXT_SENS_DATA_15 0x58 // r
#define IMU_MOTION_EXT_SENS_DATA_16 0x59 // r
#define IMU_MOTION_EXT_SENS_DATA_17 0x5A // r
#define IMU_MOTION_EXT_SENS_DATA_18 0x5B // r
#define IMU_MOTION_EXT_SENS_DATA_19 0x5C // r
#define IMU_MOTION_EXT_SENS_DATA_20 0x5D // r
#define IMU_MOTION_EXT_SENS_DATA_21 0x5E // r
#define IMU_MOTION_EXT_SENS_DATA_22 0x5F // r
#define IMU_MOTION_EXT_SENS_DATA_23 0x60 // r
#define IMU_MOTION_I2C_SLV0_D0      0x63 // r / w
#define IMU_MOTION_I2C_SLV1_D0      0x64 // r / w
#define IMU_MOTION_I2C_SLV2_D0      0x65 // r / w
#define IMU_MOTION_I2C_SLV3_D0      0x66 // r / w
#define IMU_MOTION_I2C_MST_DLY_CTRL 0x67 // r / w                   [7] DELAY_ES_SHADOW [6] reserved            [5] reserved        [4] I2C_SLV4_DLY_EN [3] I2C_SLV3_DLY_EN [2] I2C_SLV2_DLY_EN [1] I2C_SLV1_DLY_EN [0] I2C_SLV0_DLY_EN
#define IMU_MOTION_SIGNAL_PATH_RST  0x68 // r / w                   [7] reserved        [6] reserved            [5] reserved        [4] reserved        [3] reserved        [2] GYRO_RESET      [1] ACCEL_RESET     [0] TEMP_RESET
#define IMU_MOTION_MOT_DETECT_CTRL  0x69 // r / w                   [7] reserved        [6] reserved            [5] ACCEL_ON_DELAY  [4] ACCEL_ON_DELAY  [3] reserved        [2] reserved        [1] reserved        [0] reserved
#define IMU_MOTION_USER_CTRL        0x6A // r / w                   [7] reserved        [6] FIFO_EN             [5] I2C_MST_EN      [4] I2C_IF_DIS      [3] reserved        [2] FIFO_RESET      [1] I2C_MST_RESET   [0] SIG_COND_RESET
#define IMU_MOTION_PWR_MGMT_1       0x6B // r / w                   [7] DEVICE_RESET    [6] SLEEP               [5] CYCLE           [4] reserved        [3] TEMP_DIS        [2] CLKSEL          [1] CLKSEL          [0] CLKSEL
#define IMU_MOTION_PWR_MGMT_2       0x6C // r / w                   [7] LP_WAKE_CTRL    [6] LP_WAKE_CTRL        [5] STBY_XA         [4] STBY_YA         [3] STBY_ZA         [2] STBY_XG         [1] STBY_YG         [0] STBY_ZG
#define IMU_MOTION_FIFO_COUNT_H     0x72 // r / w
#define IMU_MOTION_FIFO_COUNT_L     0x73 // r / w
#define IMU_MOTION_FIFO_R_W         0x74 // r / w
#define IMU_MOTION_WHO_AM_I         0x75 // r                       [7] reserved        [6] WHO_AM_I        [5] WHO_AM_I        [4] WHO_AM_I        [3] WHO_AM_I        [2] WHO_AM_I        [1] WHO_AM_I        [0] reserved

// --- BMP085 --- https://www.sparkfun.com/datasheets/Components/General/BST-BMP085-DS000-05.pdf
#define IMU_ENVIRONMENT_ADDR        0x77 //
#define IMU_ENVIRONMENT_TEMPERATURE 0x2E //
#define IMU_ENVIRONMENT_PRESSURE0   0x34 //
#define IMU_ENVIRONMENT_PRESSURE1   0x74 //
#define IMU_ENVIRONMENT_PRESSURE2   0xB4 //
#define IMU_ENVIRONMENT_PRESSURE3   0xF4 //
#define IMU_ENVIRONMENT_CONTROL     0xF4 //
#define IMU_ENVIRONMENT_RESULT      0xF6 //
#define IMU_ENVIRONMENT_CAL_AC1     0xAA // r
#define IMU_ENVIRONMENT_CAL_AC2     0xAC // r
#define IMU_ENVIRONMENT_CAL_AC3     0xAE // r
#define IMU_ENVIRONMENT_CAL_AC4     0xB0 // r
#define IMU_ENVIRONMENT_CAL_AC5     0xB2 // r
#define IMU_ENVIRONMENT_CAL_AC6     0xB4 // r
#define IMU_ENVIRONMENT_CAL_B1      0xB6 // r
#define IMU_ENVIRONMENT_CAL_B2      0xB8 // r
#define IMU_ENVIRONMENT_CAL_MB      0xBA // r
#define IMU_ENVIRONMENT_CAL_MC      0xBC // r
#define IMU_ENVIRONMENT_CAL_MD      0xBE // r
#define IMU_ENVIRONMENT_DEVICE      0xD0 // r
#define IMU_ENVIRONMENT_DEV_ID      0x55 //
#define IMU_ENVIRONMENT_ULTRALOWPOWER 0
#define IMU_ENVIRONMENT_STANDARD      1
#define IMU_ENVIRONMENT_HIGHRES       2
#define IMU_ENVIRONMENT_ULTRAHIGHRES  3

#endif /* IMU_CONST_H_ */