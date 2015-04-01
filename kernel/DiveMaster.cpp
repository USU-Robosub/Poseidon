
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Hash.hpp"
#include "rice/String.hpp"

#include "API/ThrustController.h"
#include "API/IMUSensor.h"
#include "API/PowerManagement.h"

void dummy() {
    printf("This feature is not yet implimented.\n");
}

Rice::Object testHash() {
	Rice::String a("A");
	Rice::String b("B");
	Rice::Hash h;
	h[a] = 1;
	h[b] = 2;
	return h;
}

extern "C"
void Init_DiveMaster();
void Init_DiveMaster()
{
    Rice::Class rb_cTest = Rice::define_class("Test")
	.define_method("hash", &testHash);

    //expose ThrustController class
    Rice::Data_Type<ThrustController> rb_cThrustController =
        Rice::define_class<ThrustController>("ThrustController")
        .define_constructor(Rice::Constructor<ThrustController>())
        .define_method("setForwardThrust",  &ThrustController::setForwardThrust)
        .define_method("setStrafeThrust",   &ThrustController::setStrafeThrust)
        .define_method("setDiveThrust",     &ThrustController::setDiveThrust)
        .define_method("setYawThrust",      &ThrustController::setYawThrust)
        // - BEGIN - prototyped functions for future development
        .define_method("setRollThrust",     &dummy)
        /* provide a radius to follow and thrust velocity */
        .define_method("travelArc",         &dummy)
        /* provide an XYZ point which define forward, strafe, and dive thrust
           in order to travel a linear spacial line - provides convinience over
           calling three methods sequentially */
        .define_method("travelLine",        &dummy)
        /* stop all thrusters */
        .define_method("stopAll",           &dummy)
        /* stop forward thrusters */
        .define_method("stopForward",       &dummy)
        /* stop strafe thrusters */
        .define_method("stopStrafe",        &dummy)
        /* stop dive thrusters */
        .define_method("stopDive",          &dummy)
        /* Advanced User Access to Thrusters */
        .define_method("setForwardA",       &dummy)
        .define_method("setForwardB",       &dummy)
        .define_method("setDiveA",          &dummy)
        .define_method("setDiveB",          &dummy)
        .define_method("setStrafeA",        &dummy)
        .define_method("setStrafeB",        &dummy)
        // -  END  - 
        .define_method("accelerateForward", &ThrustController::accelerateForward)
        .define_method("accelerateStrafe",  &ThrustController::accelerateStrafe)
        .define_method("accelerateDive",    &ThrustController::accelerateDive)
        .define_method("accelerateYaw",     &ThrustController::accelerateYaw);

    //expose IMUSensor class
    Rice::Data_Type<IMUSensor> rb_cIMUSensor =
        Rice::define_class<IMUSensor>("Sensors")
        .define_constructor(Rice::Constructor<IMUSensor>())
        .define_method("temperatureA",      &IMUSensor::readTemperature)
        .define_method("temperatureB",      &IMUSensor::getTemp)
        .define_method("pressure",          &IMUSensor::readPressure)
        .define_method("sealevel",          &IMUSensor::readSealevel)
        .define_method("altitude",          &IMUSensor::readAltitude)
        .define_method("acceleration",      &IMUSensor::readAccelerometer)
        .define_method("accelX",            &IMUSensor::readAccelX)
        .define_method("accelY",            &IMUSensor::readAccelY)
        .define_method("accelZ",            &IMUSensor::readAccelZ)
        .define_method("gyroscope",         &IMUSensor::readGyroscope)
        .define_method("gyroX",             &IMUSensor::readGyroX)
        .define_method("gyroY",             &IMUSensor::readGyroY)
        .define_method("gyroZ",             &IMUSensor::readGyroZ)
        .define_method("compass",           &IMUSensor::readCompass)
        .define_method("compassX",          &IMUSensor::readCompassX)
        .define_method("compassY",          &IMUSensor::readCompassY)
        .define_method("compassZ",          &IMUSensor::readCompassZ)
        // - BEGIN - prototyped functions for future development
        .define_method("pingerDirection",   &dummy)
        .define_method("pingerMagnitude",   &dummy)
	.define_method("turnOnIMU",             &IMUSensor::turnOn)
	.define_method("turnOffIMU",            &IMUSensor::turnOff);
        // -  END  -

    //expose PowerManagement class
    Rice::Data_Type<PowerManagement> rb_cPowerManagement =
        Rice::define_class<PowerManagement>("PowerController")
        .define_constructor(Rice::Constructor<PowerManagement>())
        .define_method("turnOnESCs",        &PowerManagement::turnOnESCs)
        .define_method("turnOffESCs",       &PowerManagement::turnOffESCs)
        //.define_method("turnOnIMU", &IMUSensor::turnOn)
        //.define_method("turnOffIMU", &IMUSensor::turnOff)
        // - BEGIN - prototyped functions for future development
        .define_method("voltage",           &dummy)
        .define_method("setLEDColor",       &dummy);
        // -  END  -
}
