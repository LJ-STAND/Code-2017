#ifndef MOTOR_ARRAY_H
#define MOTOR_ARRAY_H

#include <Arduino.h>
#include <Pins.h>
#include <Common.h>
#include <MoveData.h>
#include <Motor.h>
#include <Config.h>

class MotorArray {
public:
    Motor motorRight;
    Motor motorLeft;
    Motor motorBackRight;
    Motor motorBackLeft;

    MotorArray();
    void move(int angle, int rotation, int speed);
    void move(MoveData data);
    void brake();
};

#endif // MOTOR_ARRAY_H
