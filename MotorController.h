#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

class MotorController {
public:
    MotorController(int pwmPin, int ain1Pin, int ain2Pin, int stbyPin) 
        : pwmPin(pwmPin), ain1Pin(ain1Pin), ain2Pin(ain2Pin), stbyPin(stbyPin) {
        pinMode(pwmPin, OUTPUT);
        pinMode(ain1Pin, OUTPUT);
        pinMode(ain2Pin, OUTPUT);
        pinMode(stbyPin, OUTPUT);
        digitalWrite(stbyPin, HIGH);
    }

    void setSpeed(int speed) {
        analogWrite(pwmPin, speed);
    }

    void setDirection(bool forward) {
        if (forward) {
            digitalWrite(ain1Pin, HIGH);
            digitalWrite(ain2Pin, LOW);
        } else {
            digitalWrite(ain1Pin, LOW);
            digitalWrite(ain2Pin, HIGH);
        }
    }

    void stop() {
        digitalWrite(stbyPin, LOW);
    }

private:
    int pwmPin;
    int ain1Pin;
    int ain2Pin;
    int stbyPin;
};

#endif // MOTORCONTROLLER_H
