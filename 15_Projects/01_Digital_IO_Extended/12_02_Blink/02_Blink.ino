#include "Arduino.h"
#define cLED 	13

//The setup function is called once at startup of the sketch
void setup() {
	// Add your initialization code here
	//pinMode(cLED, OUTPUT);
	DDRB = 0xFF;
}

// The loop function is called in an endless loop
void loop() {
	//Add your repeated code here
	/*digitalWrite(cLED, HIGH);
	 delay(100); // Wait for 1000 millisecond(s)
	 digitalWrite(cLED, LOW);
	 delay(100); // Wait for 1000 millisecond(s)
	 PORTB = 0xFF;*/

	PORTB |= (1<<PB5);
	_delay_ms(1000);
	PORTB = 0x00;
	//PORTB &= ~(1<<PB5);
	_delay_ms(1000);
}
