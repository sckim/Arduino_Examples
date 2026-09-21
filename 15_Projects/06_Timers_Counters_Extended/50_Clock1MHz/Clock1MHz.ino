#include "Arduino.h"
//The setup function is called once at startup of the sketch


void setup(void) {
	DDRB = _BV(DDB1);      //set OC1A/PB1 as output (Arduino pin D9, DIP pin 15)
	TCCR1A = _BV(COM1A0);              //toggle OC1A on compare match
	OCR1A = 7;                         //top value for counter
	TCCR1B = _BV(WGM12) | _BV(CS10);   //CTC mode, prescaler clock/1
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
}
