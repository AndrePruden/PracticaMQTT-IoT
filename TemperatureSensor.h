#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>

class TemperatureSensor {
public:
    TemperatureSensor(int pin) : sensorPin(pin) {}

    float readTemperature() {
        int analogValue = analogRead(sensorPin);
        float voltage = analogValue * (3.3 / 4095.0);
        return voltage * 100;
    }

private:
    int sensorPin;
};

#endif // TEMPERATURESENSOR_H
