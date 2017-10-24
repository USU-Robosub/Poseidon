/*
 * MPU6050.cpp
 *
 *  Created on: Feb 2, 2015
 * Last Edited: Feb 7, 2016
 *      Author: TekuConcept
 */

#include "MPU6050.h"


MPU6050::MPU6050() : g_full(FS_SEL::FSG_250), a_full(AFS_SEL::FSA_2) {}



MPU6050::~MPU6050() {}



int MPU6050::WhoAmI() {
  return 0;
}



float MPU6050::accel_X() {
  return 0;
}



float MPU6050::accel_Y() {
  return 0;
}



float MPU6050::accel_Z() {
  return 0;
}



float MPU6050::gyro_X(){
  return 0;
}



float MPU6050::gyro_Y() {
  return 0;
}



float MPU6050::gyro_Z() {
  return 0;
}



float MPU6050::temperature() {
  return 0;
}



float MPU6050::scaleGyro(short){
  return 0;
}



float MPU6050::scaleAccel(short) {
  return 0;
}



void MPU6050::setGyroFullScale(FS_SEL) {

}



void MPU6050::setAcclFullScale(AFS_SEL) {

}



void MPU6050::sleep() {

}



void MPU6050::awake() {

}
