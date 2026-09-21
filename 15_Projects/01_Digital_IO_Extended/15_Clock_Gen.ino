/*
 Blink
 Turns on an LED on for one second, then off for one second, repeatedly.

 Most Arduinos have an on-board LED you can control. On the Uno and
 Leonardo, it is attached to digital pin 13. If you're unsure what
 pin the on-board LED is connected to on your Arduino model, check
 the documentation at http://www.arduino.cc

 This example code is in the public domain.

 modified 8 May 2014
 by Scott Fitzgerald
 */

// the setup function runs once when you press reset or power the board
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
