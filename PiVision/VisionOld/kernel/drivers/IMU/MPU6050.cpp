/*
 * MPU6050.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: TekuConcept
 */

#include "MPU6050.h"


MPU6050::MPU6050(uint _bus_):
    bus(_bus_)
{}



MPU6050::~MPU6050()
{}



int16_t MPU6050::accel_X()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_XOUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_XOUT_L);
    return v;
}



int16_t MPU6050::accel_Y()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_YOUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_YOUT_L);
    return v;
}



int16_t MPU6050::accel_Z()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_ZOUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_ZOUT_L);
    return v;
}



int16_t MPU6050::gyro_X()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_XOUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_XOUT_L);
    return v;
}



int16_t MPU6050::gyro_Y()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_YOUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_YOUT_L);
    return v;
}



int16_t MPU6050::gyro_Z()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_ZOUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_ZOUT_L);
    return v;
}



float MPU6050::temp()
{
    int16_t v = 0;
    v = bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_TEMP_OUT_H) << 8;
    v |= bus.readByte(IMU_MOTION_ADDR_A, IMU_MOTION_TEMP_OUT_L);
    return (v / 340) + 36.53F;
}



void MPU6050::setGyroFullScale(FS_SEL select)
{
    if(select < 0 || select > 3)
        throw std::invalid_argument("selection exceeds the maximum");

    bus.writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_CONFIG, select << 3);
}



void MPU6050::setAcclFullScale(AFS_SEL select)
{
    if(select < 0 || select > 3)
        throw std::invalid_argument("selection exceeds the maximum");

    bus.writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_CONFIG, select << 3);
}



void MPU6050::sleep()
{
    bus.writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_PWR_MGMT_1, 0x40);
}



void MPU6050::awake()
{
    bus.writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_PWR_MGMT_1, 0x00);
}
