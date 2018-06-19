#include <Servo.h>
Servo servo;
int const trigPin = 5;
int const echoPin = 6;
int reply;

void setup()
{
	Serial.begin(115200);// BT 115200
	Serial.flush();
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	servo.attach(3);
}
void loop()
{
	int duration, distance;
	digitalWrite(trigPin, LOW);
	delay(1);

	digitalWrite(trigPin, HIGH);

	// Measure the pulse input in echo pin
	duration = pulseIn(echoPin, LOW);

	// Distance is half the duration devided by 29.1 (from datasheet)
	distance = (duration / 2) / 29.1;

	Serial.println(distance);

	if (distance <= 20 && distance >= 0) {
		Serial.println("Do you wanna feed?\n");

		while (Serial.available())
		{
			reply = (int)Serial.read();
			delay(60);
			if (reply)
			{
				servo.write(90);
				delay(5000);
				servo.write(0);
			}
		}
	}
	else {
		servo.write(0);
	}
	// if distance less than 0.5 meter and more than 0 (0 or less means over range) 

	// Waiting 60 ms won't hurt any one
	delay(500);
}