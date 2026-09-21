#include "Arduino.h"

int x_key = A2;        // initializing A1 for storing the joystick¡¯s x key value
int y_key = A1;        // initializing A0 for storing the joystick¡¯s y key value
int Push_Button = 2; // initializing digital pin 2 for joystick¡¯s press to select button

int Horizontal_Position = 0;       // Declaring a variable for storing the value
int y_Position = 0;                // Declaring a variable for storing the value
int button_State = 0;              // Declaring a variable for storing the value

void setup() {
	Serial.begin(9600);       // initializing serial communications at 9600 bps:

	pinMode(x_key, INPUT);           // Selecting Arduino analog A1 pin as input
	pinMode(y_key, INPUT);           // Selecting Arduino analog A0 pin as input
	pinMode(Push_Button, INPUT_PULLUP); // This will activate pull-up resistor on the push-button pin
}

void loop() {
	Horizontal_Position = analogRead(x_key); // Reading the value from A1 and storing in Horizontal_Position
	y_Position = analogRead(y_key); // Reading the value from A0 and storing in y_Position
	button_State = digitalRead(Push_Button); // Reading the digital pin 2 is high or low

	Serial.print(" Value of X key is "); // Printing ¡° Value of X key is ¡± on the disply
	Serial.print(Horizontal_Position); // Printing value of x key on the display
	Serial.print(" | Value of Y key is "); // Printing ¡° Value of Y key is ¡± on the screen
	Serial.print(y_Position);          // Printing value of y key on the display
	Serial.print(" | Button State is "); // Printing ¡° Button state ¡± on the display
	Serial.println(button_State); // Printing the button is high or low on the display

	delay(1000);                         // This will add delay between readings
}
