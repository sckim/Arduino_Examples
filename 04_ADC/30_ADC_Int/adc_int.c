#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define ADCINDEX 20
//store ADC values
uint8_t wave[ADCINDEX];
volatile uint8_t ii = 0;
volatile uint8_t flag = 0;
void USART0Init(void) {
	// Set baud rate
	UBRR0H = (uint8_t) (UBRR_VALUE >> 8);
	UBRR0L = (uint8_t) UBRR_VALUE;
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	//enable transmission and reception
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}
int USART0SendByte(char u8Data, FILE *stream) {
	//wait while previous byte is completed
	while (!(UCSR0A & (1 << UDRE0))) {
	};
	// Transmit data
	UDR0 = u8Data;
	return 0;
}
//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);
//initialize debug ports
void InitPort(void) {
	//set PD6 and PD2 as output
	DDRD |= (1 << PD2) | (1 << PD6);
}
//initialize timer0
void InitTimer0(void) {
	//Set Initial Timer value
	TCNT0 = 0;
	//Place TOP timer value to Output compare register
	OCR0A = 99;
	//Set CTC mode
	//and make toggle PD6/OC0A pin on compare match
	TCCR0A |= (1 << COM0A0) | (1 << WGM01);
}
//start timer0 with prescaller 8
void StartTimer0(void) {
	//Set prescaller 8 and start timer
	TCCR0B |= (1 << CS01);
}
void StopTimer(void) {
	TCCR0B &= ~(1 << CS01);
	TIMSK0 &= ~(1 << OCIE0A);
}
void InitADC() {
	// Select Vref=AVcc
	//and set left adjust result
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	//set prescaller to 32
	//enable autotriggering
	//enable ADC interupt
	//and enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0) | (1 << ADATE) | (1 << ADIE)
			| (1 << ADEN);
	//set ADC trigger source - Timer0 compare match A
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);
}
void SetADCChannel(uint8_t ADCchannel) {
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
}
void StartADC(void) {
	ADCSRA |= (1 << ADSC);
}
//disable ADC
void DisableADC(void) {
	ADCSRA &= ~((1 << ADEN) | (1 << ADIE));
}
//ADC conversion complete ISR
ISR(ADC_vect) {
	//clear timer compare match flag
	TIFR0 = (1 << OCF0A);
	//toggle pin PD2 to track the end of ADC conversion
	PIND = (1 << PD2);
	wave[ii++] = ADCH;
	if (ii == ADCINDEX) {
		StopTimer();
		DisableADC();
		flag = 1;
	}
}
int main() {
	//Initialize USART0
	USART0Init();
	//initialize ports
	InitPort();
	//assign our stream to standart ii/O streams
	stdout = &usart0_str;
	//initialize ADC
	InitADC();
	//select ADC channel
	SetADCChannel(0);
	//initialize timer0
	InitTimer0();
	//start timer0
	StartTimer0();
	//start conversion
	StartADC();
	//enable global interrupts
	sei();
	while (1) {
		if (flag) {
			//clear global interrupts
			cli();
			//print stored ADC values via USART
			ii = 0;
			while (ii < ADCINDEX) {
				printf("ADC val[%u] = %u\r\n", ii, wave[ii]);
				ii++;
			}
			flag = 0;
		}
	}
}
