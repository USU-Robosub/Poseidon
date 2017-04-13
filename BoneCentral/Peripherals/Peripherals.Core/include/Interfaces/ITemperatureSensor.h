#ifndef INTERFACES_I_TEMPERATURESENSOR_H
#define INTERFACES_I_TEMPERATURESENSOR_H

class ITemperatureSensor {
public:
    virtual double getTemperature() = 0;
};

#endif
