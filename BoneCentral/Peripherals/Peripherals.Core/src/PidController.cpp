//
// Created by nfcop on 7/15/2017.
//

#include "PidController.h"

PidController& PidController::withConstants(double p, double i, double d) {
    p_ = p; i_ = i; d_ = d;
    return *this;
}

PidController& PidController::withBounds(double minimum, double maximum) {
    min_ = minimum; max_ = maximum;
    return *this;
}

PidController& PidController::withTimeDelta(unsigned int timeDelta) {
    timeDelta_ = timeDelta;
    return *this;
}

double PidController::calculateAdjustmentFor(double setPoint, double processValue) {
    auto currentError = setPoint - processValue;
    auto errorDifference = currentError - previousError_;
    previousError_ = currentError;
    auto proportion  = p_ * currentError;
    auto integral  = i_ * currentError * timeDelta_;
    auto derivative  = d_ * errorDifference / timeDelta_;
    auto adjustment = proportion + integral + derivative;
    if(adjustment > max_) return max_;
    if(adjustment < min_) return min_;
    return adjustment;
}
