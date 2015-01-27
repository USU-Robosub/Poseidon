
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "API/ThrustController.h"
#include "API/IMUSensor.h" //todo: expand

extern "C"
void Init_APIWrapper()
{
    Rice::Data_Type<ThrustController> rb_cThrustController =
        Rice::define_class<ThrustController>("ThrustController")
        .define_constructor(Rice::Constructor<ThrustController>())
        .define_method("achieveXRate", &ThrustController::achieveXRate)
        .define_method("achieveYRate", &ThrustController::achieveYRate)
        .define_method("achieveZRate", &ThrustController::achieveZRate)
        .define_method("achieveYawRate", &ThrustController::achieveYawRate)
        .define_method("achieveRollRate", &ThrustController::achieveRollRate);
}
