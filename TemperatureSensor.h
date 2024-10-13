#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>

class TemperatureSensor {
public:
    TemperatureSensor(int pin) : pin(pin) {}

    float read() {
        int analogValue = analogRead(pin);
        float voltage = analogValue * (3.3 / 4095.0);
        return voltage * 100;
    }

private:
    int pin;
};

#endif // TEMPERATURE_SENSOR_H
