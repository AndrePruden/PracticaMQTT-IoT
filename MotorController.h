#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>

class MotorController {
public:
    MotorController(int pwmPin, int ain1Pin, int ain2Pin, int stbyPin)
        : pwmPin(pwmPin), ain1Pin(ain1Pin), ain2Pin(ain2Pin), stbyPin(stbyPin) {}

    void setup() {
        pinMode(pwmPin, OUTPUT);
        pinMode(ain1Pin, OUTPUT);
        pinMode(ain2Pin, OUTPUT);
        pinMode(stbyPin, OUTPUT);
        digitalWrite(stbyPin, HIGH);
        digitalWrite(ain1Pin, HIGH);
        digitalWrite(ain2Pin, LOW);
    }

private:
    int pwmPin;
    int ain1Pin;
    int ain2Pin;
    int stbyPin;
};

#endif // MOTOR_CONTROLLER_H
