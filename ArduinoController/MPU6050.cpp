/*
 * MPU6050.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: TekuConcept
 */

#include "MPU6050.h"


MPU6050::MPU6050()
{}



MPU6050::~MPU6050()
{}



int16_t MPU6050::accel_X()
{
    return I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_XOUT_H);
}



int16_t MPU6050::accel_Y()
{
    return I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_YOUT_H);
}



int16_t MPU6050::accel_Z()
{
    return I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_ZOUT_H);
}



int16_t MPU6050::gyro_X()
{
    return I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_XOUT_H);
}



int16_t MPU6050::gyro_Y()
{
    return I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_YOUT_H);
}



int16_t MPU6050::gyro_Z()
{
    return I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_ZOUT_H);
}



float MPU6050::temperature()
{
    return (I2C_Utils::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_TEMP_OUT_H) / 340) + 36.53F;
}



void MPU6050::setGyroFullScale(FS_SEL select)
{
    if(select < 0 || select > 3)
        return;

    I2C_Utils::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_CONFIG, select << 3);
}



void MPU6050::setAcclFullScale(AFS_SEL select)
{
    if(select < 0 || select > 3)
        return;

    I2C_Utils::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_CONFIG, select << 3);
}



void MPU6050::sleep()
{
    I2C_Utils::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_PWR_MGMT_1, 0x40);
}



void MPU6050::awake()
{
    I2C_Utils::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_PWR_MGMT_1, 0x00);
}

