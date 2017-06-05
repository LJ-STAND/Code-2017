#include "MotorArray.h"

MotorArray::MotorArray() {
    motorRight = Motor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_SB, MOTOR_RIGHT_ANGLE, MOTOR_RIGHT_REVERSED);
    motorLeft = Motor(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_SB, MOTOR_LEFT_ANGLE, MOTOR_LEFT_REVERSED);
    motorBackRight = Motor(MOTOR_BACK_RIGHT_PWM, MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_RIGHT_SB, MOTOR_BACK_RIGHT_ANGLE, MOTOR_BACK_RIGHT_REVERSED);
    motorBackLeft = Motor(MOTOR_BACK_LEFT_PWM, MOTOR_BACK_LEFT_IN1, MOTOR_BACK_LEFT_IN2, MOTOR_BACK_LEFT_SB, MOTOR_BACK_LEFT_ANGLE, MOTOR_BACK_LEFT_REVERSED);
}

void MotorArray::move(int angle, int rotation, int speed) {
    angle = mod(90 - angle, 360);

    double a = cos(degreesToRadians(angle)) / sin(degreesToRadians(MOTOR_ANGLE));
    double b = sin(degreesToRadians(angle)) / cos(degreesToRadians(MOTOR_ANGLE));

    double motorRightValue = a - b;
    double motorBackRightValue = -a - b;
    double motorBackLeftValue = b - a;
    double motorLeftValue = a + b;

    double updatedSpeed = (double) speed / doubleAbs(fmax(fmax(fmax(doubleAbs(motorLeftValue), doubleAbs(motorRightValue)), doubleAbs(motorBackRightValue)), doubleAbs(motorBackLeftValue)));

    int motorRightSpeed = (int) round(motorRightValue * updatedSpeed) + rotation;
    int motorLeftSpeed = (int) round(motorLeftValue * updatedSpeed) + rotation;
    int motorBackRightSpeed = (int) round(motorBackRightValue * updatedSpeed) + rotation;
    int motorBackLeftSpeed = (int) round(motorBackLeftValue * updatedSpeed) + rotation;

    double updatedSpeed2 = (double) 255 / doubleAbs(fmax(fmax(fmax(doubleAbs(motorLeftSpeed), doubleAbs(motorRightSpeed)), doubleAbs(motorBackRightSpeed)), doubleAbs(motorBackLeftSpeed)));

    if (updatedSpeed2 < 1) {
        int motorRightSpeed = (int) round(motorRightSpeed * updatedSpeed2);
        int motorLeftSpeed = (int) round(motorLeftSpeed * updatedSpeed2);
        int motorBackRightSpeed = (int) round(motorBackRightSpeed * updatedSpeed2);
        int motorBackLeftSpeed = (int) round(motorBackLeftSpeed * updatedSpeed2);
    }

    motorRight.move(motorRightSpeed);
    motorLeft.move(motorLeftSpeed);
    motorBackRight.move(motorBackRightSpeed);
    motorBackLeft.move(motorBackLeftSpeed);
}

void MotorArray::move(MoveData data) {
    move(data.angle, data.rotation, data.speed);
}

void MotorArray::brake() {
    motorRight.brake();
    motorLeft.brake();
    motorBackRight.brake();
    motorBackLeft.brake();
}
