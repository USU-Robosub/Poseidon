//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"
using json = nlohmann::json;

#ifdef DEBUG
#define IF_DEBUG if(true)
#else
#define IF_DEBUG if(false)
#endif

CommandDispatcher::CommandDispatcher(std::istream& in, std::ostream& out,
    ImuSensor& imuSensor, ThrustController& thrustController,
    PowerManager& powerManager, IHeadlights& lights, ILogger& logger)
        : in_(in),
          out_(out),
          imuSensor_(imuSensor),
          thrustController_(thrustController),
          powerManager_(powerManager),
          lights_(lights),
          logger_(logger),
          shouldExit_(false) {}

void CommandDispatcher::runLoop() {
    while(!shouldExit_) {
        std::string cmd;
        std::getline(in_, cmd);
        std::stringstream ss(cmd);
        dispatchCommand(ss);
    }
}

void CommandDispatcher::dispatchCommand(std::stringstream& cmdString) {
    std::string cmd;
    cmdString >> cmd;
    if (cmd == "startThrusters")                start();
    else if(cmd == "move")                      move( cmdString );
    else if(cmd == "yaw")                       yaw( cmdString );
    else if(cmd == "dive")                      dive( cmdString );
    else if(cmd == "killThrusters")             kill();
    else if(cmd == "configureYaw")              configureYaw( cmdString );
    else if(cmd == "configureTimeDelta")        configureTimeDelta( cmdString );
    else if(cmd == "turnOnEscs")                powerManager_.turnOnEscs();
    else if(cmd == "turnOffEscs")               powerManager_.turnOffEscs();
    else if(cmd == "switchLights")              lights_.switchLights();
    else if(cmd == "turnOnImu")                 powerManager_.turnOnImuSensor();
    else if(cmd == "turnOffImu")                powerManager_.turnOffImuSensor();
    else if(cmd == "getAcceleration")           _getAcceleration();
    else if(cmd == "getAngularAcceleration")    _getAngularAcceleration();
    else if(cmd == "getHeading")                _getHeading();
    else if(cmd == "getInternalTemperature")    _getInternalTemperature();
    else if(cmd == "getInternalPressure")       _getInternalPressure();
    else if(cmd == "getExternalTemperature")    _getExternalTemperature();
    else if(cmd == "getExternalPressure")       _getExternalPressure();
    else if(cmd == "exit")                      shouldExit_ = true;
    else                                        logger_.warning( "Invalid command" );
}



void CommandDispatcher::start() {
    IF_DEBUG {
        std::cout << "Started Thrusters" << std::endl;
    }
    thrustController_.start();
}

void CommandDispatcher::move(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IF_DEBUG {
        std::cout << "Move: " << throttle << std::endl;
    }
    thrustController_.move( throttle );
}

void CommandDispatcher::dive(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IF_DEBUG {
        std::cout << "Dive: " << throttle << std::endl;
    }
    thrustController_.dive( throttle );
}

void CommandDispatcher::yaw(std::stringstream &cmdString) {
    float angle;
    cmdString >> angle;
    IF_DEBUG {
        std::cout << "Yaw: " << angle << std::endl;
    }
    thrustController_.yaw( angle );
}

void CommandDispatcher::kill() {
    IF_DEBUG {
        std::cout << "Killed Thrusters" << std::endl;
    }
    thrustController_.kill();
}

void CommandDispatcher::configureYaw(std::stringstream &cmdString) {
    PidController::Configuration config;
    cmdString >> config.P >> config.I >> config.D;
    thrustController_.configureYaw( config );
}


void CommandDispatcher::configureTimeDelta(std::stringstream& cmdString) {
    unsigned int timeDelta;
    cmdString >> timeDelta;
    thrustController_.configureTimeDelta( timeDelta );
}




void CommandDispatcher::_getAcceleration() {
    auto data = imuSensor_.getAcceleration();
    auto accelJson = json{
            {"Type", "Acceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    IF_DEBUG {
        std::cerr << accelJson << std::endl;
    }
    out_ << accelJson << std::endl;
}

void CommandDispatcher::_getAngularAcceleration() {
    auto data = imuSensor_.getAngularAcceleration();
    auto accelJson = json{
            {"Type", "AngularAcceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    IF_DEBUG {
        std::cerr << accelJson << std::endl;
    }
    out_ << accelJson << std::endl;
}

void CommandDispatcher::_getHeading() {
    auto headingJson = imuSensor_.getHeading().toJson();
    headingJson["Type"] = "Heading";
    IF_DEBUG {
        std::cerr << headingJson << std::endl;
    }
    out_ << headingJson << std::endl;
}

void CommandDispatcher::_getInternalTemperature() {
    auto data = imuSensor_.getIntTemperature();
    out_ << json{{"Type", "InternalTemperature"},{"Value",data}} << std::endl;
}

void CommandDispatcher::_getInternalPressure() {
    auto data = imuSensor_.getIntPressure();
    out_ << json{{"Type", "InternalPressure"},{"Value",data}} << std::endl;
}

void CommandDispatcher::_getExternalTemperature() {
    auto data = imuSensor_.getExtTemperature();
    out_ << json{{"Type", "ExternalTemperature"},{"Value",data}} << std::endl;
}

void CommandDispatcher::_getExternalPressure() {
    auto data = imuSensor_.getExtPressure();
    out_ << json{{"Type", "ExternalPressure"},{"Value",data}} << std::endl;
}

#ifdef IF_DEBUG
#undef IF_DEBUG
#endif
