#define cbi(sfr, bit)      (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit)      (_SFR_BYTE(sfr) |= _BV(bit))

// from TCNT = (CS / 16000000 ) * (256-x) =10msec
// x = time * (16000000/CS)
// 15625*8msec = 125
#define cDelay 125

ISR(TIMER0_COMPA_vect)
{
	digitalWrite(13, digitalRead(13)^1);
}

ISR(TIMER0_COMPB_vect)
{
	digitalWrite(12, digitalRead(12)^1);
}

// 핀 하나하나를 개별적으로 제어하여 프로그램하는 예
void setup() {
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);

	//cli();
	noInterrupts();

	TIMSK0 |= _BV(OCIE0A);
	TIMSK0 |= _BV(OCIE0B);

	TCCR0A |= (1 << WGM01);		// Fast PWM mode
	TCCR0A |= (1 << WGM00);

	//CS0[2:0]  1/64
    cbi(TCCR0B, CS02);  // <=> TCCR0B |= _BV(CS01)
    sbi(TCCR0B, CS01);
    cbi(TCCR0B, CS00);

	sbi(TCCR0A, COM0B1);  	// PD5 output  set
	sbi(TCCR0A, COM0B0);  	// PD6 output set
    OCR0B = cDelay/2;

	sbi(TCCR0A, COM0A1);  	// PD6 output set
    cbi(TCCR0A, COM0A0);  	// PD6 output set
	OCR0A = cDelay;

	//sei();
	interrupts();
}

void loop() {
	// foreground로 처리할 작업들
  	//OCR0A = map(analogRead(A0), 0, 1023, 0, 255);
    //OCR0B = map(analogRead(A1), 0, 1023, 0, 255);
}
