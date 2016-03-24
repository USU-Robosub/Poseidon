//
// Created by Kevin Burgon on 03/08/2016
//

#include <ITemperatureSensor.h>

class MockTemperatureSensor : public ITemperatureSensor {
public:
    float getTemperature() {return 0;}
};
