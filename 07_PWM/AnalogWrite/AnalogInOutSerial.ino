void setup() {
	// initialize serial communications at 9600 bps:
	Serial.begin(115200);
	pinMode(13, OUTPUT);

	TCCR0B &= ~_BV(CS02);
	TCCR0B |= _BV(CS01);
	TCCR0B |= _BV(CS00);

	//analogWrite(6, 128);  	// 1kHz, timer 0
	pinMode(6, OUTPUT);
	DDRD |= _BV(PD6);
	TCCR0A |= _BV(COM0A1);
	OCR0A = 10;

	//analogWrite(5, 10);  	// 1kHz, timer 0
	pinMode(5, OUTPUT);
	DDRD |= _BV(PD5);
	TCCR0A |= _BV(COM0B1);
	OCR0B = 20;

	//analogWrite(9, 128);		// 500Hz, timer 1
	pinMode(9, OUTPUT);

	TCCR1A |= _BV(WGM10);  //phase correct mode

	TCCR1B = 0; // prescaler
	// set timer 1 prescale factor to 64
	TCCR1B |= _BV(CS11);
	TCCR1B |= _BV(CS10);

	TCCR1A |= _BV(COM1A1);
	OCR1A = 10; // set pwm duty

	//analogWrite(10, 128);		// 500Hz, timer 1
	//analogWrite(11, 128);		// 500Hz, timer 2
	// change the analog out value:
	//analogWrite(3, 128);	// 500Hz, timer 2

}

/* Arduino UNO에서 PWM은
 *
 * Arduino Pins 5 and 6: 1kHz, timer 0
 * Arduino Pins 9, 10, 11, and 3: 500Hz, timer 1, 2
 *
 * 아래 사이트에 자세히 나와 있음
 * https://arduino-info.wikispaces.com/Arduino-PWM-Frequency
 */

int index = 0;
void loop() {
	//delay(500);
}
