#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
	int motorAngle;

	Motor() {}
	Motor(int pwm, int inOne, int inTwo, int standby, int angle, bool reverse = false);

	void move(int speed);
	void brake();

private:
	int pwmPin;
	int inOnePin;
	int inTwoPin;
	int standbyPin;
	bool reversed;
};

#endif
