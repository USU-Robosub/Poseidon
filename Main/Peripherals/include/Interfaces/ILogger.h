//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_LOGGER_H
#define PERIPHERALS_I_LOGGER_H

class ILogger {
public:
    virtual void info(const char message[]) = 0;
    virtual void warning(const char message[]) = 0;
    virtual void error(const char message[]) = 0;
};

#endif //PERIPHERALS_I_LOGGER_H
