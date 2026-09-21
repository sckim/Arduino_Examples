#include "Arduino.h"
#define cLED	13

//The setup function is called once at startup of the sketch
void setup() {
	// Add your initialization code here
	pinMode(LED_BUILTIN, OUTPUT);
}

// The loop function is called in an endless loop
void loop() {
	//Add your repeated code here
	digitalWrite(cLED, HIGH);
	delay(1000); // Wait for 1000 millisecond(s)
	digitalWrite(cLED, LOW);
	delay(1000); // Wait for 1000 millisecond(s)
}
