
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "API/ThrustController.h"
#include "API/IMUSensor.h"
#include "API/PowerManagement.h"

void dummy() {
    printf("This feature is not yet implimented.\n");
}

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
        .define_method("setForwardThrust", &ThrustController::setForwardThrust)
        .define_method("setStrafeThrust", &ThrustController::setStrafeThrust)
        .define_method("setDiveThrust", &ThrustController::setDiveThrust)
        .define_method("setYawThrust", &ThrustController::setYawThrust)
        // - BEGIN - prototyped functions for future development
        .define_method("setRollThrust", &dummy)
        /* provide a radius to follow and thrust velocity */
        .define_method("travelArc", &dummy)
        /* provide an XYZ point which define forward, strafe, and dive thrust
           in order to travel a linear spacial line - provides convinience over
           calling three methods sequentially */
        .define_method("travelLine", &dummy)
        /* stop all thrusters */
        .define_method("stopAll", &dummy)
        /* stop forward thrusters */
        .define_method("stopForward", &dummy)
        /* stop strafe thrusters */
        .define_method("stopStrafe", &dummy)
        /* stop dive thrusters */
        .define_method("stopDive", &dummy)
        /* Advanced User Access to Thrusters */
        .define_method("setForwardA", &dummy)
        .define_method("setForwardB", &dummy)
        .define_method("setDiveA", &dummy)
        .define_method("setDiveB", &dummy)
        .define_method("setStrafeA", &dummy)
        .define_method("setStrafeB", &dummy)
        // -  END  - 
        .define_method("accelerateForward", &ThrustController::accelerateForward)
        .define_method("accelerateStrafe", &ThrustController::accelerateStrafe)
        .define_method("accelerateDive", &ThrustController::accelerateDive)
        .define_method("accelerateYaw", &ThrustController::accelerateYaw);

    //expose IMUSensor class
    Rice::Data_Type<IMUSensor> rb_cIMUSensor =
        Rice::define_class<IMUSensor>("Sensors")
        .define_constructor(Rice::Constructor<IMUSensor>())
        .define_method("temperatureA", &dummy/*&IMUSensor::readTemperature)*/)
        .define_method("temperatureB", &dummy/*&IMUSensor::getTemp*/)
        .define_method("pressure", &dummy/*&IMUSensor::readPressure*/)
        .define_method("sealevel", &dummy/*&IMUSensor::readSealevel*/)
        .define_method("altitude", &dummy/*&IMUSensor::readAltitude*/)
        // - BEGIN - prototyped functions for future development
        .define_method("accelX", &dummy)
        .define_method("accelY", &dummy)
        .define_method("accelZ", &dummy)
        .define_method("gyroX", &dummy)
        .define_method("gyroY", &dummy)
        .define_method("gyroZ", &dummy)
        .define_method("compassX", &dummy)
        .define_method("compassY", &dummy)
        .define_method("compassZ", &dummy)
        .define_method("pingerDirection", &dummy)
        .define_method("pingerMagnitude", &dummy);
        // -  END  -

    //expose PowerManagement class
    Rice::Data_Type<PowerManagement> rb_cPowerManagement =
        Rice::define_class<PowerManagement>("PowerController")
        .define_constructor(Rice::Constructor<PowerManagement>())
        .define_method("turnOnESCs", &dummy/*&PowerManagement::turnOnESCs*/)
        .define_method("turnOffESCs", &dummy/*&PowerManagement::turnOffESCs*/)
        // - BEGIN - prototyped functions for future development
        .define_method("voltage", &dummy)
        .define_method("setLEDColor", &dummy);
        // -  END  -
}
