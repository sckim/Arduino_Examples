#include <Arduino.h>
#include "Arduino.h"
#include "Stepper.h"

// change this to fit the number of steps per revolution
// for your motor
const int stepsPerRevolution = 4;

// initialize the stepper library on pins 4 through 7:
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);

//The setup function is called once at startup of the sketch
void setup() {
	// set the speed at 10 rpm:
	myStepper.setSpeed(30);

	// step one revolution  in one direction:
	//Serial.println("clockwise");
	myStepper.step(stepsPerRevolution+1);
	delay(500);

	// step one revolution in the other direction:
	Serial.println("counterclockwise");
	myStepper.step(-stepsPerRevolution);
	delay(500);
}

// The loop function is called in an endless loop
void loop() {
}
