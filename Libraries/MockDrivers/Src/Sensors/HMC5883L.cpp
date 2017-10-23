/*
 * HMC5883L.cpp
 *
 *  Created on: Jan 31, 2015
 * Last Edited: Feb  7, 2016
 *      Author: TekuConcept
 */

#include "HMC5883L.h"


HMC5883L::HMC5883L() : currentGain(Gain::G1_3) {}



HMC5883L::~HMC5883L() {}



int HMC5883L::WhoAmI() {
  return 0;
}



float HMC5883L::X() {
  return 0;
}



float HMC5883L::Y() {
  return 0;
}



float HMC5883L::Z() {
  return 0;
}



float HMC5883L::scaleWithGain(short) {
  return 0;
}



bool HMC5883L::isLocked() {
  return true;
}



bool HMC5883L::isReady() {
  return true;
}



void HMC5883L::setSampleAverage(Sample) {

}



void HMC5883L::setOutputRate(Rate) {

}



void HMC5883L::setGain(Gain) {

}



void HMC5883L::setMode(Mode) {

}



int HMC5883L::getSampleAverage() {
  return 0;
}



int HMC5883L::getOutputRate() {
  return 0;
}



int HMC5883L::getGain() {
  return 0;
}



int HMC5883L::getMode() {
  return 0;
}
