#ifndef MOTOR_ARRAY_H
#define MOTOR_ARRAY_H

#include <Arduino.h>
#include "Motor.h"

class MotorArray {
public:
    Motor motorLeft;
    Motor motorRight;
    Motor motorBack;

    MotorArray();
    void move(int direction, int rotation, int speed);
    void brake();
};

#endif // MOTOR_ARRAY_H
