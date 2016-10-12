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

void Motor::set(int power) {
	if (power > 0) {
		analogWrite(pwmPin, constrain(power, 0, 255));

		if (reversed) {
			digitalWrite(inOnePin, HIGH);
			digitalWrite(inTwoPin, LOW);
		} else {
			digitalWrite(inOnePin, LOW);
			digitalWrite(inTwoPin, HIGH);
		}
	} else if (power < 0) {
		analogWrite(pwmPin, constrain(abs(power), 0, 255));

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
