//
// Created by Nathan Copier on 11/20/2015.
//

#include "RubyLogger.h"

RubyLogger::RubyLogger(std::shared_ptr<std::ostream> out) : out_(out) { }

void RubyLogger::info(const char *const message) {
    *out_ << "info " << message << std::endl;
}

void RubyLogger::warning(const char *const message) {
    *out_ << "warning " << message << std::endl;
}

void RubyLogger::error(const char *const message) {
    *out_ << "error " << message << std::endl;
}
