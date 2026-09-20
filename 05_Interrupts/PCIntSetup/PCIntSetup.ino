#include "Arduino.h"
// Install Pin change interrupt for a pin, can be called multiple times

void pciSetup(byte pin) {
	PCICR |= bit(digitalPinToPCICRbit(pin)); // enable interrupt for the group
	*digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));  // enable pin

	// pin 7
	PCICR |= bit(2);
	PCMSK2 |= bit(7);

	// pin 8
	PCICR |= bit(0);
	PCMSK0 |= bit(0);

	// pin 14
	PCICR |= bit(1);
	PCMSK1 |= bit(0);

	//PCIFR |= bit(digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
}

// Use one Routine to handle each group

ISR (PCINT0_vect)	// handle pin change interrupt for D8 to D13 here
{
	digitalWrite(12, digitalRead(8));
}

ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
	digitalWrite(13, digitalRead(A0) or digitalRead(A1));
}

ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
	digitalWrite(11, digitalRead(7));
}

void setup() {
// set pullups, if necessary
	/*
	 for (int i = 0; i <= 12; i++)
	 digitalWrite(i, HIGH);  // pinMode( ,INPUT) is default

	 for (i = A0; i <= A5; i++)
	 digitalWrite(i, HIGH);
	 */
	pinMode(7, INPUT_PULLUP);
	pinMode(8, INPUT_PULLUP);
	pinMode(A0, INPUT_PULLUP);
	pinMode(A1, INPUT_PULLUP);

	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);  // LED

	digitalWrite(11, HIGH);
	digitalWrite(12, HIGH);
	digitalWrite(13, HIGH);
	// enable interrupt for pin...
	pciSetup(7);
	pciSetup(8);
	pciSetup(A0);
	pciSetup(A1);

	//PCICR &= ~_BV(0);
	//PCMSK0 |= 2;
}

void loop() {
	// Nothing needed
}

/*
 //pciSetup(7);
 PCICR |= 0x04; //PCICR |= _BV(PCIE2); //0b00000100
 PCMSK2 |= _BV(PCINT23);

 //pciSetup(8);
 PCICR |= 0x01; //PCICR |= _BV(PCIE0); //0b00000001
 PCMSK0 |= _BV(PCINT0);

 //pciSetup (A0);
 //pciSetup (A1);
 PCICR |= 0x02; //PCICR |= _BV(PCIE1); //0b00000010
 PCMSK1 |= _BV(PCINT8);
 PCMSK1 |= _BV(PCINT9);
 */
