#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <AFMotor.h>

int sensorDistancePin = A1;
int sensorDistanceValue = 0;
int distance = 0;
int temp = 0;
bool deschis = false;
int ledVerde = A2;
int ledRosu = A3;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
AF_DCMotor motor(1);

void actionareMotor(int directie) {
	motor.run(directie);
	delay(3000);
	motor.run(RELEASE);
}

void setup() {
	// put your setup code here, to run once:
	pinMode(sensorDistancePin, INPUT);
	Serial.begin(9600);
	motor.setSpeed(255);
	motor.run(RELEASE);
	actionareMotor(FORWARD);
	mlx.begin();
}

void loop() {
	// put your main code here, to run repeatedly:
	if (!deschis) {
		Serial.println("Usa inchisa");
		sensorDistanceValue = analogRead(sensorDistancePin);
		distance = (6762/(sensorDistanceValue-9))-4;
	
		Serial.print("Distanta: ");
		Serial.println(distance);
	
		if (distance <= 15) {
			temp = mlx.readObjectTempC();
			Serial.print("Temperatura citita: ");
			Serial.println(temp);
	
			if (temp < 33) {
				Serial.println("Usa se deschide");
				actionareMotor(BACKWARD);
				deschis = true;
			} else {
				Serial.println("Temperatura prea mare!!");
				delay(5000);
			}
		} else {
			Serial.println("Apropiati-va");
		}
	} else {
		Serial.println("Usa deschisa");
		delay(5000);
		deschis = false;
		Serial.println("Usa se inchide");
		actionareMotor(FORWARD);
	}

	Serial.println();
	delay(1000);
}
