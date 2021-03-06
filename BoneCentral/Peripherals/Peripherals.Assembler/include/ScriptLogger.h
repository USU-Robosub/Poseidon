//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_SCRIPT_LOGGER_H
#define PERIPHERALS_SCRIPT_LOGGER_H

#include <ostream>
#include <memory>
#include <mutex>
#include <ILogger.h>

class ScriptLogger : public ILogger {

private:
    std::ostream& out_;
    std::mutex loggerLock_;

public:
    ScriptLogger(std::ostream& out);
    void info(const char message[]);
    void warning(const char message[]);
    void error(const char message[]);

};


#endif //PERIPHERALS_SCRIPT_LOGGER_H
