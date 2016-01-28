//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <ThrustController.h>
#include <IMUSensor.h>
#include <PowerManagement.h>
#include "RubyLogger.h"
#include "PwmThrusterFactory.h"
#include "ImuFactory.h"
#include "PowerModule/CMPR.h"

void setupPipes(int readPipe[2], int writePipe[2]);
void runControllers();
void signalHandler(int sigNum);

int main() {

    // TODO: Replace pipes with shared memory
    int thrusterPipe[2];
    int loggerPipe[2];
    pipe(thrusterPipe);
    pipe(loggerPipe);

    if(fork()) {
        setupPipes(thrusterPipe, loggerPipe);
        signal(SIGPIPE, signalHandler);
        runControllers();
    }
    else {
        setupPipes(loggerPipe, thrusterPipe);
        // TODO: Add the name of the actual ruby app
        execl("ruby", "{ruby_app}");
    }

    return 0;

}

void setupPipes(int readPipe[2], int writePipe[2]) {

    close(readPipe[1]);
    dup2(readPipe[0], STDIN_FILENO);
    close(writePipe[0]);
    dup2(writePipe[1], STDOUT_FILENO);

}

void signalHandler(int sigNum) {
    if( sigNum == 13 ) exit(0);
    exit(sigNum);
}

void runControllers() {

    auto rubyLogger = std::make_shared<RubyLogger>(&std::cout);

    auto thrusterFactory = PwmThrusterFactory();
    ThrustController tc(thrusterFactory, rubyLogger);

    auto imuFactory = ImuFactory();
    IMUSensor imu(imuFactory, rubyLogger);

    auto powerModule = std::make_shared<PowerModule>(I2C_SUB2);
    PowerManagement pm(powerModule, rubyLogger);

    wait(NULL);

}

