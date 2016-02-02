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
    int16_t v = 0;
    v = readByte(IMU_MOTION_ACCEL_XOUT_H);
    return v;
}



int16_t MPU6050::accel_Y()
{
    int16_t v = 0;
    v = readByte(IMU_MOTION_ACCEL_YOUT_H);
    return v;
}



int16_t MPU6050::accel_Z()
{
    int16_t v = 0;
    v = readByte(IMU_MOTION_ACCEL_ZOUT_H);
    return v;
}



int16_t MPU6050::gyro_X()
{
    int16_t v = 0;
    v = readByte(IMU_MOTION_GYRO_XOUT_H);
    return v;
}



int16_t MPU6050::gyro_Y()
{
    int16_t v = 0;
    v = readByte(IMU_MOTION_GYRO_YOUT_H);
    return v;
}



int16_t MPU6050::gyro_Z()
{
    int16_t v = 0;
    v = readByte(IMU_MOTION_GYRO_ZOUT_H);
    return v;
}



float MPU6050::temp()
{
    int16_t v = 0;
    v = read16(IMU_MOTION_TEMP_OUT_H);
    return (v / 340) + 36.53F;
}



void MPU6050::setGyroFullScale(FS_SEL select)
{
    if(select < 0 || select > 3)
        return;

    writeByte(IMU_MOTION_GYRO_CONFIG, select << 3);
}



void MPU6050::setAcclFullScale(AFS_SEL select)
{
    if(select < 0 || select > 3)
        return;

    writeByte(IMU_MOTION_ACCEL_CONFIG, select << 3);
}



void MPU6050::sleep()
{
    writeByte(IMU_MOTION_PWR_MGMT_1, 0x40);
}



void MPU6050::awake()
{
    writeByte(IMU_MOTION_PWR_MGMT_1, 0x00);
}



uint8_t MPU6050::readByte(uint8_t addr)
{
    Wire.beginTransmission(IMU_MOTION_ADDR_A);
    Wire.write(byte(addr));
    Wire.endTransmission();
    Wire.requestFrom(IMU_MOTION_ADDR_A, 1);

    return static_cast<uint8_t>(Wire.read());
}


uint16_t MPU6050::read16(uint8_t addr)
{
    Wire.beginTransmission(IMU_MOTION_ADDR_A);
    Wire.write(byte(addr));
    Wire.endTransmission();
    Wire.requestFrom(IMU_MOTION_ADDR_A, 2);

    return static_cast<uint16_t>(Wire.read()<<8 | Wire.read());
}


void MPU6050::writeByte(uint8_t addr, uint8_t data)
{
    Wire.beginTransmission(IMU_MOTION_ADDR_A);
    Wire.write(byte(addr));
    Wire.write(byte(data));
    Wire.endTransmission();
}

