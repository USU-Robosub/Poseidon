//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_RUBY_LOGGER_H
#define PERIPHERALS_RUBY_LOGGER_H

#include <ostream>
#include <memory>
#include <ILogger.h>

class RubyLogger : public ILogger {

private:
    std::shared_ptr<std::ostream> out_;

public:
    RubyLogger(std::ostream* out);
    void info(const char message[]);
    void warning(const char message[]);
    void error(const char message[]);

};


#endif //PERIPHERALS_RUBY_LOGGER_H
