#include <avr/io.h>
#include <avr/interrupt.h>

// from TCNT = (CS / 16000000 ) * (256-x) =10msec
// x = time * (16000000/CS)
// 15625*8msec = 125
#define cDelay 100

// 핀 하나하나를 개별적으로 제어하여 프로그램하는 예
void setup() {
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);

	noInterrupts(); // global interrupt disable = cli()
	TIMSK0 |= (1 << OCIE0A);    // Timer0 Compare match interrupt
	TIMSK0 |= (1 << OCIE0B);    // Timer0 Compare match interrupt

	TCCR0A |= (1 << WGM01);		// Fast PWM mode
	TCCR0A |= (1 << WGM00);

	//CS0[2:0]
	TCCR0B |= (1 << CS01);	// Clock/1024
	TCCR0B |= (1 << CS00);	// Clock/1024

	TCCR0A |= _BV(COM0B1);  	// PD5 output  set
	//TCCR0A |= _BV(COM0B0);  	// PD5 output
	OCR0B = cDelay/2;

	TCCR0A |= _BV(COM0A1);  	// PD6 output
	//TCCR0A |= _BV(COM0A0);  	// PD6 output
	OCR0A = cDelay;

	interrupts();  // global interrupt enable = sei()

	Serial.begin(9600);
}

void loop() {
	// foreground로 처리할 작업들
}

//ISR (TIMER0_OVF_vect) {
ISR(TIMER0_COMPB_vect) {
	digitalWrite(12, digitalRead(12) ^ 1);
}

ISR(TIMER0_COMPA_vect) {
	//background로 처리할 작업들
	digitalWrite(13, digitalRead(13) ^ 1);
}

int main(void) {
	setup();

	while (1) {
		loop();
	}
}
