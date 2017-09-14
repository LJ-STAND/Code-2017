#ifndef PID_H
#define PID_H

class PID {
public:
    double kp;
    double ki;
    double kd;

    PID(double p, double i, double d);
    double update(double input, double setpoint, double modulus = 0.0);

private:
    unsigned long lastTime;

    double integral;
    double lastInput;
}

#endif
