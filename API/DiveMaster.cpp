
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "API/ThrustController.h"
#include "API/IMUSensor.h"

extern "C"
void Init_DiveMaster();
void Init_DiveMaster()
{
    Rice::Data_Type<ThrustController> rb_cThrustController =
        Rice::define_class<ThrustController>("ThrustController")
        .define_constructor(Rice::Constructor<ThrustController>())
        .define_method("achieveXRate", &ThrustController::achieveXRate)
        .define_method("achieveYRate", &ThrustController::achieveYRate)
        .define_method("achieveZRate", &ThrustController::achieveZRate)
        .define_method("achieveYawRate", &ThrustController::achieveYawRate)
        .define_method("achieveRollRate", &ThrustController::achieveRollRate);

    Rice::Data_Type<IMUSensor> rb_cIMUSensor =
        Rice::define_class<IMUSensor>("IMUSensor")
        .define_constructor(Rice::Constructor<IMUSensor>())
        .define_method("readInteriorTemperature", &IMUSensor::readInteriorTemperature)
        .define_method("readPressure", &IMUSensor::readPressure)
        .define_method("readSealevelPressure", &IMUSensor::readSealevelPressure)
        .define_method("readAltitude", &IMUSensor::readAltitude);
}
