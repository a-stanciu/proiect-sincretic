// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

// DC motor on M2
AF_DCMotor motor(1);

void setup() {
	motor.setSpeed(255);
	motor.run(RELEASE);
}

void loop() {
	motor.run(FORWARD);
	delay(3000);
	motor.run(RELEASE);
	motor.run(BACKWARD);
	delay(3000);
	motor.run(RELEASE);

//	motor.run(BACKWARD);
//	delay(3000);
//	motor.run(RELEASE);
}
