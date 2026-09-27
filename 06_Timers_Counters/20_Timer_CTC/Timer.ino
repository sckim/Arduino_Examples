/*************************************
 * Purpose: Timer0을 이용하여 1초마다 overflow
 * interrupt에 의한 LED Shift
 *
 * TIMSK0
 * TCCR0A
 * TCCR0B
 * TCNT0
 *************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char SEG[10] = {0b11000000, 0b11111001,
                         0b10100100, 0b10110000,
                         0b10011001, 0b10010010,
                         0b10000010, 0b11111000,
                         0b10000000, 0b10010000};

// from TCNT = (CS / 16000000 ) * (256-x) =10msec
// x = time * (16000000/CS)
// 15625*8msec = 125
#define cDelay 125

volatile int sec = 0;
volatile int msec8 = 0;

// 핀 하나하나를 개별적으로 제어하여 프로그램하는 예
void setup()
{
  for(int i=0; i<8; i++) {
	  pinMode(i, OUTPUT);  // pin의 입출력 상태 결정
  //	digitalWrite(i, HIGH); // 현재 pin 출력을 high
  }
  pinMode(13, OUTPUT);

  cli();
  TIMSK0 |= (1 << OCIE0A);    // Timer0 Compare match interrupt
  TCCR0A |= (1<<WGM01);
  TCCR0A |= _BV(COM0A0);

  //CS0[2:0]
  TCCR0B |= (1 << CS02);	// Clock/1024
  TCCR0B |= (1 << CS00);	// Clock/1024

  OCR0A = cDelay;
  sei();
}

void dispSeg(unsigned char ch)
{
	for(int i=0; i<8; i++)
      digitalWrite(i, SEG[ch] & (1<<i));
}

void loop()
{
   // foreground로 처리할 작업들
}

//ISR (TIMER0_OVF_vect) {
ISR(TIMER0_COMPA_vect) {
  //background로 처리할 작업들
	msec8++;
	if (msec8 == 125) {
		msec8 = 0;
	//	dispSeg(sec++);
		digitalWrite(13, digitalRead(13)^1);
	}
	if (sec > 9) {
		sec = 0;
	}
}

int main(void)
{
  setup();

  while(1) {
  	loop();
  }
}
