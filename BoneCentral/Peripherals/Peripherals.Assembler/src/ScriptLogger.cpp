//
// Created by Nathan Copier on 11/20/2015.
//

#include "ScriptLogger.h"

ScriptLogger::ScriptLogger(std::ostream& out) : out_(out) { }

void ScriptLogger::info(const char *const message) {
    std::lock_guard<std::mutex> guard(loggerLock_);
    out_ << "info " << message << std::endl;
}

void ScriptLogger::warning(const char *const message) {
    std::lock_guard<std::mutex> guard(loggerLock_);
    out_ << "warn " << message << std::endl;
}

void ScriptLogger::error(const char *const message) {
    std::lock_guard<std::mutex> guard(loggerLock_);
    out_ << "error " << message << std::endl;
}
