/*
 * MPU6050.cpp
 *
 *  Created on: Feb 2, 2015
 * Last Edited: Feb 7, 2016
 *      Author: TekuConcept
 */

#include "MPU6050.h"


MPU6050::MPU6050() {}



MPU6050::~MPU6050() {}



int16_t MPU6050::accel_X() {
    return I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_XOUT_H);
}



int16_t MPU6050::accel_Y() {
    return I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_YOUT_H);
}



int16_t MPU6050::accel_Z() {
    return I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_ZOUT_H);
}



int16_t MPU6050::gyro_X(){
    return I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_XOUT_H);
}



int16_t MPU6050::gyro_Y() {
    return I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_YOUT_H);
}



int16_t MPU6050::gyro_Z() {
    return I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_ZOUT_H);
}



float MPU6050::temperature() {
    int16_t v = 0;
    v = I2C::readShort(IMU_MOTION_ADDR_A, IMU_MOTION_TEMP_OUT_H);
    return (v / 340) + 36.53F;
}



void MPU6050::setGyroFullScale(FS_SEL select) {
    I2C::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_GYRO_CONFIG, static_cast<int>(select) << 3);
}



void MPU6050::setAcclFullScale(AFS_SEL select) {
    I2C::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_ACCEL_CONFIG, static_cast<int>(select) << 3);
}



void MPU6050::sleep() {
    I2C::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_PWR_MGMT_1, 0x40);
}



void MPU6050::awake() {
    I2C::writeByte(IMU_MOTION_ADDR_A, IMU_MOTION_PWR_MGMT_1, 0x00);
}
