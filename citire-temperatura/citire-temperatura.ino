#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
	Serial.begin(9600);
	mlx.begin();
}

void loop() {
	Serial.print("Temperatura ambientala: ");
	Serial.println(mlx.readAmbientTempC());
	
	Serial.print("Temperatura obiect: ");
	Serial.println(mlx.readObjectTempC());
	
	Serial.println();
	delay(500);
}
