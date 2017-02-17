#include "MotorArray.h"

MotorArray::MotorArray() {
    motorRight = Motor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_SB, 60, true);
    motorLeft = Motor(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_SB, 300, true);
    motorBackRight = Motor(MOTOR_BACK_RIGHT_PWM, MOTOR_BACK_RIGHT_IN1, MOTOR_BACK_RIGHT_IN2, MOTOR_BACK_RIGHT_SB, 120, true);
    motorBackLeft = Motor(MOTOR_BACK_LEFT_PWM, MOTOR_BACK_LEFT_IN1, MOTOR_BACK_LEFT_IN2, MOTOR_BACK_LEFT_SB, 240, true);
}

void MotorArray::move(int angle, int rotation, int speed) {
    double angleRadians = degreesToRadians(360 - angle);

    double motorRightValue = cos(degreesToRadians(motorRight.motorAngle + 90) - angleRadians);
    double motorLeftValue = cos(degreesToRadians(motorLeft.motorAngle + 90) - angleRadians);
    double motorBackRightValue = cos(degreesToRadians(motorBackRight.motorAngle + 90) - angleRadians);
    double motorBackLeftValue = cos(degreesToRadians(motorBackLeft.motorAngle + 90) - angleRadians);

    double updatedSpeed = (double) speed / doubleAbs(fmax(fmax(fmax(doubleAbs(motorLeftValue), doubleAbs(motorRightValue)), doubleAbs(motorBackRightValue)), doubleAbs(motorBackLeftValue)));

    int motorRightSpeed = (int) round(motorRightValue * updatedSpeed) + rotation;
    int motorLeftSpeed = (int) round(motorLeftValue * updatedSpeed) + rotation;
    int motorBackRightSpeed = (int) round(motorBackRightValue * updatedSpeed) + rotation;
    int motorBackLeftSpeed = (int) round(motorBackLeftValue * updatedSpeed) + rotation;

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
