#ifndef MOTOR_ARRAY_H
#define MOTOR_ARRAY_H

#include "Motor.h"

class MotorArray {
public:
    Motor motorLeft;
    Motor motorRight;
    Motor motorBack;

    void MotorController();
    void move(int direction, int rotation, int power);
private:
    
};

#endif // MOTOR_ARRAY_H
