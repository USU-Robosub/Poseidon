//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_PRESSURE_SENSOR_H
#define PERIPHERALS_MOCK_PRESSURE_SENSOR_H

#include <IPressureSensor.h>

class MockPressureSensor : public IPressureSensor {
public:
    bool initialize(uint8_t mode){ return 0; };
    float readTemperature(void){ return 0; };
    int32_t readPressure(void){ return 0; };
    int32_t readSealevelPressure(float altitude_meters){ return 0; };
    float readAltitude(float sealevelPressure){ return 0; };
};


#endif //PERIPHERALS_MOCK_PRESSURE_SENSOR_H
