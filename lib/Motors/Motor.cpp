#include "Motor.h"

Motor::Motor(int pwm, int inOne, int inTwo, int standby, int angle, bool reverse) {
	pwmPin = pwm;
	inOnePin = inOne;
	inTwoPin = inTwo;
	standbyPin = standby;
	motorAngle = angle;
	reversed = reverse;

	pinMode(pwm, OUTPUT);
	pinMode(inOne, OUTPUT);
	pinMode(inTwo, OUTPUT);
	pinMode(standbyPin, OUTPUT);
}

void Motor::set(int speed) {
	if (speed > 0) {
		analogWrite(pwmPin, constrain(speed, 0, 255));

		if (reversed) {
			digitalWrite(inOnePin, HIGH);
			digitalWrite(inTwoPin, LOW);
		} else {
			digitalWrite(inOnePin, LOW);
			digitalWrite(inTwoPin, HIGH);
		}
	} else if (speed < 0) {
		analogWrite(pwmPin, constrain(abs(speed), 0, 255));

		if (reversed) {
			digitalWrite(inOnePin, LOW);
			digitalWrite(inTwoPin, HIGH);
		} else {
			digitalWrite(inOnePin, HIGH);
			digitalWrite(inTwoPin, LOW);
		}
	} else {
		analogWrite(pwmPin, 255);
		digitalWrite(inOnePin, LOW);
		digitalWrite(inTwoPin, LOW);
	}

	digitalWrite(standbyPin, HIGH);
}

void Motor::brake() {
	set(0);
}
