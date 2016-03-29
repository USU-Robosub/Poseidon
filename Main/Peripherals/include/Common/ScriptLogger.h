//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_RUBY_LOGGER_H
#define PERIPHERALS_RUBY_LOGGER_H

#include <ostream>
#include <memory>
#include <ILogger.h>

class ScriptLogger : public ILogger {

private:
	// fixes "error in "./x" free() invalid pointer 0xXXXX"
    std::ostream * out_;

public:
    ScriptLogger(std::ostream* out);
    void info(const char message[]);
    void warning(const char message[]);
    void error(const char message[]);

};


#endif //PERIPHERALS_RUBY_LOGGER_H
