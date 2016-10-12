#include "MotorArray.h"

MotorArray::MotorArray() {
    motorLeft = Motor(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_SB, 60, true);
    motorRight = Motor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_SB, 300, true);
    motorBack = Motor(MOTOR_BACK_PWM, MOTOR_BACK_IN1, MOTOR_BACK_IN2, MOTOR_BACK_SB, 180, true);
}

MotorArray::move(int direction, int rotation, int speed) {
    double directionAngleRadians = degreesToRadians(360 - direction);

    double motorLeftValue = cos(degreesToRadians(motorLeft.motorAngle + 90) - directionAngleRadians);
    double motorRightValue = cos(degreesToRadians(motorRight.motorAngle + 90) - directionAngleRadians);
    double motorBackValue = cos(degreesToRadians(motorBack.motorAngle + 90) - directionAngleRadians);

    double updatedSpeed = (double) speed / doubleAbs(fmax(fmax(doubleAbs(motorLeftValue), doubleAbs(motorRightValue)), doubleAbs(motorBackValue)));

    int motorLeftSpeed = (int) round(motorLeftValue * updatedSpeed) + rotation;
    int motorRightSpeed = (int) round(motorRightValue * updatedSpeed) + rotation;
    int motorBackSpeed = (int) round(motorBackValue * updatedSpeed) + rotation;

    motorLeft.set(motorLeftSpeed);
    motorRight.set(motorRightSpeed);
    motorBack.set(motorBackSpeed);
}
