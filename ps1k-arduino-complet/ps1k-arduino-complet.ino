#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <AFMotor.h>

int buton = A0;
int sensorDistancePin = A1;
int ledVerde = A2;
int ledRosu = A3;

int sensorDistanceValue = 0;
int distance = 0;
int temp = 0;
bool deschis = false;
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
	actionareMotor(FORWARD);
	motor.run(RELEASE);
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
				digitalWrite(ledVerde, HIGH);
				actionareMotor(BACKWARD);
				deschis = true;
				delay(5000);
				actionareMotor(FORWARD);
				deschis = false;
				Serial.println("Usa blocata, apasati buton.");
				while (true) {
					if (analogRead(buton) == 1023) {
						actionareMotor(BACKWARD);
						delay(2000);
						break;
					}
				}
				actionareMotor(FORWARD);
			} else {
				Serial.println("Temperatura prea mare!!");
				digitalWrite(ledRosu, HIGH);
				delay(5000);
				digitalWrite(ledRosu, LOW);
			}
		} else {
			Serial.println("Apropiati-va");
			digitalWrite(ledVerde, LOW);
			digitalWrite(ledRosu, LOW);
		}
	} else {
		Serial.println("Usa deschisa");
		delay(5000);
		deschis = false;
		Serial.println("Usa se inchide");
		actionareMotor(FORWARD);
		digitalWrite(ledVerde, LOW);
	}

	Serial.println();
	delay(1000);
}
