/*
 ADC
 */

volatile int val = 0;
volatile int flag = 0;

ISR(ADC_vect)
{
	TIFR0 |= (1 << OCF0A);
	TCNT0 = 0;

	val = ADC;
	flag = 1;
}

void InitTimer0(void) {
	//Set Initial Timer value
	TCNT0 = 0;
	//Place TOP timer value to Output compare register
	OCR0A = 99;
	//Set CTC mode
	//and make toggle PD6/OC0A pin on compare match
	TCCR0A |= (1 << COM0A0) | (1 << WGM01);
}

void StartTimer0(void) {
	//Set prescaller 8 and start timer
	TCCR0B |= (1 << CS01);
}

void SetADCChannel(uint8_t ADCchannel) {
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
}

void InitADC() {
	// Select Vref=AVcc
	//and set left adjust result
	//ADMUX |= (1 << REFS0) | (1 << ADLAR);
	ADMUX |= (1 << REFS0);
	//set prescaller to 32
	//enable autotriggering
	//enable ADC interupt
	//and enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0) | (1 << ADATE) | (1 << ADIE)
			| (1 << ADEN);
	//set ADC trigger source - Timer0 compare match A
//	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);
}

void StartADC(void) {
	ADCSRA |= (1 << ADSC);
}

void setup() {
	Serial.begin(9600);

	InitADC();
	SetADCChannel(0);

//	InitTimer0();
//	StartTimer0();
	StartADC();
	sei();
}

void loop() {
	if (flag) {
		cli();
		Serial.print("ADC[0] = ");
		Serial.print(val);
		Serial.print(", ");
		Serial.print(map(val, 0, 1023, 0, 5000) / 1000.0, 2);
		Serial.println("V");
		//    delay(500);
		flag = 0;
		//StartADC();
		sei();
	}
}
