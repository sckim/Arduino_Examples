#include "Arduino.h"
// Controlling 2 Servos Using a Joystick.

#include <Servo.h>                       // including the library of servo motor

#define ServoH_Min 0
#define ServoH_Max 100

int First_Signal_Pin = 6;                // initializing pin 6 for first servo
int Second_Signal_Pin = 7;         // initializing pin 7 for first servo

int Horizontal_Joystick_Pin = A1;  // initializing A0 for horizontal movement
int Vertical_Joystick_Pin = A2;  // initializing A1 for vertical movement

// initializing the min and max values for horizontal and vertical movement
int Horizontal_Min = 0;
int Horizontal_Max = 180;
int Vertical_Min = 0;
int Vertical_Max = 180;

Servo First_Servo;
Servo Second_Servo;

// Declaring variables for storing values
int Horizontal_Value;
int Horizontal_Servo_Value;
int Vertical_Value;
int Vertical_Servo_Value;

void setup() {
	First_Servo.attach(First_Signal_Pin);      // Enabling pin 6 for first servo
	Second_Servo.attach(Second_Signal_Pin);    // Enabling pin 7 for first servo
}

void loop() {
	Horizontal_Value = analogRead(Horizontal_Joystick_Pin); // Reading the value from A0
	Vertical_Value = analogRead(Vertical_Joystick_Pin); // Reading the value from A1

// Mapping the values for horizontal and vertical movement of joystick.
	Horizontal_Servo_Value = map(Horizontal_Value, 0, 1023, ServoH_Min,
			ServoH_Max);

	Vertical_Servo_Value = map(Vertical_Value, 0, 1023, ServoH_Min, ServoH_Max);

// Moving the servos

	First_Servo.write(Horizontal_Servo_Value);
	Second_Servo.write(Vertical_Servo_Value);

	delay(2000);    // Delay of 2 seconds

}
