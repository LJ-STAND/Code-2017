#include "PID.h"

PID::PID(double p, double i, double d) {
    kp = p;
    ki = i;
    kd = d;

    lastTime = micros();
}

double PID::update(double input, double setpoint, double modulus) {
    double derivative;
    double error = setpoint - input;

    unsigned long currentTime = micros();
    double elapsedTime = (currentTime - lastTime) / 1000000.0;
    lastTime = currentTime;

    integral += elapsedTime * error;

    if(modulus != 0.0) {
        double difference = (input - lastInput);

        if (difference < -modulus) {
            difference += modulus;
        } else if (difference > modulus) {
            difference -= modulus;
        }

        derivative = difference / elapsedTime;
    } else {
        derivative = (input - lastInput) / elapsedTime;
    }
    lastInput = input;
    return kp * error + ki * integral + kd * derivative;
}
