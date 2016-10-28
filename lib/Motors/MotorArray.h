#ifndef MOTOR_ARRAY_H
#define MOTOR_ARRAY_H

#include <Arduino.h>
#include "Motor.h"

class MotorArray {
public:
    Motor motorRight;
    Motor motorLeft;
    Motor motorBackRight;
    Motor motorBackLeft;

    MotorArray();
    void move(int direction, int rotation, int speed);
    void brake();
};

#endif // MOTOR_ARRAY_H
