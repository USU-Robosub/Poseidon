
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "API/ThrustController.h"
#include "API/IMUSensor.h"
#include "API/PowerManagement.h"

extern "C"
void Init_DiveMaster();
void Init_DiveMaster()
{
    //expose Vector3D class
    Rice::Data_Type<Vector3D> rb_cVector3D =
        Rice::define_class<Vector3D>("Vector3D")
        .define_constructor(Rice::Constructor<Vector3D>())
        .define_method("setTo", &Vector3D::setTo)
        .define_method("setX", &Vector3D::setX)
        .define_method("setY", &Vector3D::setY)
        .define_method("setZ", &Vector3D::setZ)
        .define_method("getX", &Vector3D::setX)
        .define_method("getY", &Vector3D::setY)
        .define_method("getZ", &Vector3D::setZ);

    //expose ThrustController class
    Rice::Data_Type<ThrustController> rb_cThrustController =
        Rice::define_class<ThrustController>("ThrustController")
        .define_constructor(Rice::Constructor<ThrustController>())
        .define_method("achieveXRate", &ThrustController::achieveXRate)
        .define_method("achieveYRate", &ThrustController::achieveYRate)
        .define_method("achieveZRate", &ThrustController::achieveZRate)
        .define_method("achieveYawRate", &ThrustController::achieveYawRate)
        .define_method("achieveRollRate", &ThrustController::achieveRollRate);

    //expose IMUSensor class
    Rice::Data_Type<IMUSensor> rb_cIMUSensor =
        Rice::define_class<IMUSensor>("IMUSensor")
        .define_constructor(Rice::Constructor<IMUSensor>())
        .define_method("readInteriorTemperature", &IMUSensor::readInteriorTemperature)
        .define_method("readPressure", &IMUSensor::readPressure)
        .define_method("readSealevelPressure", &IMUSensor::readSealevelPressure)
        .define_method("readAltitude", &IMUSensor::readAltitude)
        .define_method("readCompass", &IMUSensor::ruby_Compass)
        .define_method("readAcceleration", &IMUSensor::ruby_Acceleration)
        .define_method("readGyro", &IMUSensor::ruby_Gyro)
        .define_method("readTemperature", &IMUSensor::getTemp);

    //expose PowerManagement class
    Rice::Data_Type<PowerManagement> rb_cPowerManagement =
        Rice::define_class<PowerManagement>("PowerManagement")
        .define_constructor(Rice::Constructor<PowerManagement>())
        .define_method("turnOnESCs", &PowerManagement::turnOnESCs)
        .define_method("turnOffESCs", &PowerManagement::turnOffESCs);
}
