//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"
using json = nlohmann::json;

#ifdef DEBUG
#define IFDEBUG if(true)
#else
#define IFDEBUG if(false)
#endif

CommandDispatcher::CommandDispatcher(std::istream& in, std::ostream& out,
    ImuSensor& imuSensor, ThrustController& thrustController,
    PowerManager& powerManager, IHeadlights& lights, IVoltage& voltage)
        : in_(in),
          out_(out),
          imuSensor_(imuSensor),
          thrustController_(thrustController),
          powerManager_(powerManager),
          lights_(lights),
          voltmeter_(voltage),
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
    if(cmd == "goDirection")                    goDirection(cmdString);
    else if(cmd == "rotate")                    rotate(cmdString);
    else if(cmd == "move")                      move(cmdString);
    else if(cmd == "secondaryDive")             strafe(cmdString);
    else if(cmd == "primaryDive")               dive(cmdString);
    else if(cmd == "yaw")                       yaw(cmdString);
    else if(cmd == "pitch")                     pitch(cmdString);
    else if(cmd == "roll")                      roll(cmdString);
    else if(cmd == "killThrust")                kill();
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
    else if(cmd == "measureVoltage")            _getVoltage();
    else if(cmd == "exit")                      shouldExit_ = true;
}




void CommandDispatcher::goDirection(std::stringstream& cmdString) {
    float move, strafe, dive;
    cmdString >> move >> strafe >> dive;
    IFDEBUG {
        std::cout << "Move: " << move;
        std::cout << " Strafe: " << strafe;
        std::cout << " Dive: " << dive << std::endl;
    }
    thrustController_.goDirection(move, strafe, dive);
}

void CommandDispatcher::rotate(std::stringstream& cmdString) {
    float yaw, pitch, roll;
    cmdString >> yaw >> pitch >> roll;
    IFDEBUG {
        std::cout << "Yaw: " << yaw;
        std::cout << " Pitch: " << pitch;
        std::cout << " Roll: " << roll << std::endl;
    }
    thrustController_.rotate(yaw, pitch, roll);
}

void CommandDispatcher::move(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IFDEBUG {
        std::cout << "Move: " << throttle << std::endl;
    }
    thrustController_.move(throttle);
}

void CommandDispatcher::strafe(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IFDEBUG {
        std::cout << "Strafe: " << throttle << std::endl;
    }
    thrustController_.strafe(throttle);
}

void CommandDispatcher::dive(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IFDEBUG {
        std::cout << "Dive: " << throttle << std::endl;
    }
    thrustController_.dive(throttle);
}

void CommandDispatcher::yaw(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IFDEBUG {
        std::cout << "Yaw: " << throttle << std::endl;
    }
    thrustController_.yaw(throttle);
}

void CommandDispatcher::pitch(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IFDEBUG {
        std::cout << "Pitch: " << throttle << std::endl;
    }
    thrustController_.pitch(throttle);
}

void CommandDispatcher::roll(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
    IFDEBUG {
        std::cout << "Roll: " << throttle << std::endl;
    }
    thrustController_.roll(throttle);
}

void CommandDispatcher::kill() {
    IFDEBUG {
        std::cout << "Killed Thrusters" << std::endl;
    }
    thrustController_.killAllThrusters();
}




void CommandDispatcher::_getAcceleration() {
    auto data = imuSensor_.getAcceleration();
    auto accelJson = json{
            {"Type", "Acceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    IFDEBUG {
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
    IFDEBUG {
        std::cerr << accelJson << std::endl;
    }
    out_ << accelJson << std::endl;
}

void CommandDispatcher::_getHeading() {
    auto data = imuSensor_.getHeading();
    auto headingJson = json{
            {"Type", "Heading"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    IFDEBUG {
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

void CommandDispatcher::_getVoltage() {
    auto data = voltmeter_.measureVoltage();
    auto voltJson = json{
        {"Type", "Voltage"},
        {"Value", data}
    };
    IFDEBUG {
        std::cerr << voltJson << std::endl;
    }
    out_ << voltJson << std::endl;
}

#ifdef IFDEBUG
#undef IFDEBUG
#endif